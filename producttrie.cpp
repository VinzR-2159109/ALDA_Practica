//Vinz Roosen & Lars Gielen
#include "producttrie.h"

#include <algorithm>
#include <iostream>
#include <fstream>

ProductTrie::ProductTrie()
    : m_head{new Node}
{ }

/**
 * Deze (hulp) functie doet het volgende:
 *      - Maak alle mogelijke unieke suffix strings aan van de asin en de titel van het product
 *      - Insert al deze strings in de trie
 *      - Time hoe lang het duurd om een product in de trie te zetten
 *
 * De werking van insertProductInternal en createAllSuffixes wordt verder uitgelegd bij de functie zelf.
 */
void ProductTrie::insertProduct(Product *product)
{
    auto startTime = std::chrono::high_resolution_clock::now();

    {
        QStringList prefixes = createAllSuffixes(product->getAsin());
        for (const QString &string : prefixes) {
            insertProductInternal(string, product);
        }
    }

    {
        QStringList prefixes = createAllSuffixes(product->getTitle());
        for (const QString &string : prefixes) {
            insertProductInternal(string, product);
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

    addToCSV(duration.count(), "../QVector.csv");

    emit productInserted(duration.count());
}

/**
 *  Deze functie zoekt alle producten die searchString als substring hebben.
 *  Dit wordt gedaan door de searchString op te zoeken in de trie. Elke node heeft een lijst (QSet) van producten,
 *  hierdoor is het mogelijk om, zodra de laatste node van de searchString gevonden is, alle producten terug te geven.
 *
 *  Een woord opzoeken in een trie kan in O(k) tijd gedaan worden, waarbij k staat voor het aantal karakters in de searchString.
 *
 *  Gemiddeld wordt deze functie uitgevoerd tussen de 3-25 µs op de geteste pc, maar dit hangt zeer sterk af van de lengte van de searchString.
 */
QVector<Product*> ProductTrie::search(QString searchString)
{
    auto startTime = std::chrono::high_resolution_clock::now();

    Node *currentNode = m_head;

    for (QChar value : searchString.toLower()) {
        if (currentNode->children.find(value) == currentNode->children.end()) {
            return QVector<Product*>();
        }

        currentNode = currentNode->children[value];
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

    emit searchComplete(duration.count());

    return QVector<Product*>(currentNode->products.begin(), currentNode->products.end());;
}

QVector<Product*> ProductTrie::searchSorted(QString searchString, int numberOfSortedElements)
{
    auto startTime = std::chrono::high_resolution_clock::now();

    QVector<Product*> products = search(searchString);

    int numElements = std::min(static_cast<int>(products.size()), numberOfSortedElements);
    std::partial_sort(products.begin(), products.begin() + numElements, products.end(),
        [](const Product *a, const Product *b) {
            return a->getDiscount() > b->getDiscount();
        }
    );

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);

    emit searchComplete(duration.count());

    return products;
}

/**
 * Deze functie insert een product met de gegeven insertString.
 * Dit wordt gedaan door de insertString aan te maken in de trie. Elke node heeft een QSet van producten. Hier wordt de pointer naar het
 * product opgeslagen (als deze nog niet in de QSet te vinden is).
 *
 * Het product wordt in elke node waar de string langskomt opgeslagen, op deze manier kan je het product vinden als het einde van de tring mist.
 * Als je ook alle prefixes van de string in de trie zet, kan je ook een product vinden met eender welke substring.
 *
 * Tijdcomplexiteit:
 *      - Inserten van woord in trie: O(k) -> k = #chars in string
 *      - Inserten van product in (meestal) QVector = O(1)
 *      - Sorteren van sortedProducts = O(n log(n)) en n = 11;
 *
 * De totale tijdscomplexiteit van deze functie is dus O(n log(n) + k).
 *
 * Na testen van verschillende collecties voor het opslaan van de producten in de nodes:
 *      - QSet: ~11ms -> overschrijven van waarden
 *      - QVector: ~4ms???? -> contains gebruiken
 *
 * Er is een verschil tussen de gemiddelde waardes bij het inserten van de eerste producten en de producten die later worden geinsert.
 *      - Begin: rond de 150 ms
 *      - Later: rond de 70 ms
 *
 * Een mogelijke verklaring hiervoor is dat er in het begin meer nodes moeten aangemaakt worden, bij de latere producten zijn deze al aangemaakt
 * waardoor het inserten minder tijd in beslag neemt.
 *
 */
void ProductTrie::insertProductInternal(QString insertString, Product *product)
{
    Node *currentNode = m_head;

    for (QChar value : insertString) {
        if (currentNode->children.find(value) == currentNode->children.end()) {
            currentNode->children[value] = new Node;
        }

        currentNode = currentNode->children[value];

        // Voor QSet:
        // currentNode->products.insert(product);

        // Voor QVector:
        if (!currentNode->products.contains(product)) {
            currentNode->products.push_back(product);
        }
    }
}

/**
 * Deze functie maakt alle suffixes van de gegeven string.
 * Het maken van alle prefixes van een string wordt gedaan in O(n) tijd.
 */
QStringList ProductTrie::createAllSuffixes(QString string)
{
    QStringList suffixes;
    string = string.toLower();
    for (int i = 0; i < string.length(); ++i) {
        suffixes.push_back(string.mid(i));
    }
    return suffixes;
}

void ProductTrie::addToCSV(int value, const std::string& filename) {
    // Open the CSV file in append mode
    std::ofstream csvFile;
    csvFile.open(filename, std::ios::app);

    // Check if the file is successfully opened
    if (!csvFile.is_open()) {
        std::cout << "Error opening file: " << filename << std::endl;
        return;
    }

    // Append the integer value to the CSV file
    csvFile << value << ",";

    // Close the file
    csvFile.close();
}
