#include "producttrie.h"

ProductTrie::ProductTrie()
    : m_head{new Node}
{ }

/**
 * Deze (hulp) functie doet het volgende
 *      - Maak alle mogelijke unieke substrings aan van de Asin en de titel van het product
 *      - Insert deze strings allemaal in de trie
 *      - Time hoe lang het duurd om een product in de trie te zetten
 *
 * Er is een verschil tussen de gemiddelde waardes bij het inserten van de eerste producten en de producten die later worden geinsert.
 *      - Begin: rond de 150 ms
 *      - Later: rond de 70 ms
 *
 * Een mogelijke verklaring hiervoor is dat er in het begin meer nodes moeten aangemaakt worden, bij de latere producten zijn deze al aangemaakt
 * waardoor het inserten minder tijd in beslag neemt.
 *
 * De werking van insertProductInternal en createAllUniqueSearchStrings wordt verder uitgelegd bij de functie zelf.
 */
void ProductTrie::insertProduct(Product *product)
{
    auto startTime = std::chrono::high_resolution_clock::now();

    QSet<QString> substrings = createAllUniqueSearchStrings({product->getAsin(), product->getTitle()});
    for (const QString &string : substrings) {
        insertProductInternal(string, product);
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    emit productInserted(duration.count());
}

/**
 *  Deze functie zoekt alle producten die searchString als substring hebben.
 *  Dit wordt gedaan door de searchString op te zoeken in de trie. Elke node heeft een lijst (QMultiMap) van producten,
 *  hierdoor is het mogelijk om, zodra de laatste node van de searchString gevonden is, alle producten terug te geven.
 *
 *  Een woord opzoeken in een trie kan in O(k) tijd gedaan worden, waarbij k staat voor het aantal karakters in de searchString.
 *
 *  Gemiddeld wordt deze functie uitgevoerd tussen de 3-25 µs op de geteste pc, maar dit hangt zeer sterk af van de lengte van de searchString.
 */
QMultiMap<float, Product*> ProductTrie::autoComplete(QString searchString)
{
    auto startTime = std::chrono::high_resolution_clock::now();

    Node *currentNode = m_head;

    for (QChar value : searchString.toLower()) {
        if (currentNode->children.find(value) == currentNode->children.end()) {
            return QMultiMap<float, Product*>();
        }

        currentNode = currentNode->children[value];
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

    emit searchComplete(duration.count());
    return currentNode->products;
}

/**
 * Deze functie insert een product met de gegeven insertString.
 * Dit wordt gedaan door de insertString aan te maken in de trie. Elke node heeft een QMultiMap van producten,
 * hierdoor is het mogelijk om, zodra de laatste node van de insertString gevonden is, het product toe te voegen aan de QMultiMap van deze node.
 * Bij het toevoegen van het product wordt de korting als key genomen en de pointer naar het product als value, op deze manier is de QMultiMap
 * gesorteerd op korting.
 *
 * Een woord inserten in een trie kan in O(k) tijd gedaan worden, waarbij k staat voor het aantal karakters in de searchString.
 *
 * QMultiMap is gelijkaardig aan std::multimap, die geimplementeerd is als een gebalanceerde binary search tree.
 * De value inserten in de QMultiMap kan dus gedaan worden in O(log n) tijd, waarbij n staat voor het aantal waardes in de QMultiMap.
 *
 * De totale tijdscomplexiteit van deze functie is dus O(log n + k) waar n staat voor voor het aantal waardes in de QMultiMap
 * en k staat voor het aantal karakters in de searchString.
 */
void ProductTrie::insertProductInternal(QString insertString, Product *product)
{
    Node *currentNode = m_head;

    for (QChar value : insertString.toLower()) {
        if (currentNode->children.find(value) == currentNode->children.end()) {
            currentNode->children[value] = new Node;
        }

        currentNode = currentNode->children[value];
    }

    currentNode->products.insert(product->getDiscount(), product);
}

/**
 * Deze functie maakt alle mogelijke unieke substrings aan van de gegeven strings voor een product.
 * Het maken van alle substrings van een string wordt gedaan in O(n²) tijd, en dit wordt voor elke string in strings.
 *
 * De substrings worden allemaal in een QSet geinsert. Een QSet heeft unieke keys waardoor we kunnen garanderen dat er geen dubbele substrings in de
 * trie raken.
 *
 * Inserten in een QSet is O(1).
 */
QSet<QString> ProductTrie::createAllUniqueSearchStrings(QStringList strings)
{
    QSet<QString> substrings = QSet<QString>();
    for (QString string: strings) {
        string = string.toLower();
        for (int i = 0; i < string.length(); ++i) {
            for (int j = 1; j <= string.length() - i; ++j) {
                substrings.insert(string.mid(i, j));
            }
        }
    }
    return substrings;
}
