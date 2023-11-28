//Vinz Roosen & Lars Gielen
#include "producttrie.h"

#include <algorithm>
#include <iostream>
#include <fstream>

ProductTrie::ProductTrie()
    : m_head{new Node}
{ }

/**
 * Deze functie doet het volgende:
 *      - Maak alle mogelijke suffix strings aan van de asin en de titel van het product
 *      - Insert al deze strings in de trie
 *      - Time hoe lang het duurd om een product in de trie te zetten
 *
 * De werking van insertProductInternal en createAllSuffixes wordt verder uitgelegd bij de functie zelf.
 *
 * // Sorteren bij inserten of bij zoeken:
 *      - Sorteren bij inserten:
 *          + sneller zoeken (~15 µs)
 *          - langere laadtijd bij het inladen
 *          - moet opnieuw gebeuren als de prijs van een product veranderd / als een product toegevoegd/verwijderd wordt
 *      - Sorteren bij het zoeken
 *          - minder snel zoeken (~15 ms)
 *          + minder lang laadtijd bij het insterten
 *          + producten kunnen veranderen zonder extra impact te hebben
 *
 *  We hebben volgende manieren bekeken:
 *      - Alle producten bewaren in een multimap met als key de korting en als value het product
 *          -> Inserten is O(log n) voor elk karakter in de insertString -> O(k log(n))
 *          -> Inserten duurde te veel te lang
 *      - De 10 producten met de hoogste korting bewaren in een aparte gesorteerde vector
 *          -> Inserten met insertsort is O(n) met n een vaste waarde (10 in dit geval) -> O(10 * k)
 *      - Alle producten sorteren met std::sort
 *          -> Zoeken duurd iets langer maar onmerkbaar bij het gebruiken
 *          -> Inserten is zo snel mogelijk
 *      - De producten gedeeltelijk sorteren met std::partial_sort
 *          -> zoeken is iets sneller met dezelfde functionaliteit
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

    emit productInserted(duration.count());
}

/**
 *  Deze functie zoekt alle producten die searchString als substring hebben.
 *  Dit wordt gedaan door de searchString op te zoeken in de trie. Elke node heeft een lijst (QSet) van producten,
 *  hierdoor is het mogelijk om, zodra de laatste node van de searchString gevonden is, alle producten terug te geven.
 *
 *  Een woord opzoeken in een trie kan in O(k) tijd gedaan worden, waarbij k staat voor het aantal karakters in de searchString.
 *
 *  // Bij het opzoeken van 'b' met 5000 producten
 *      - Gevonden producten: 5000
 *      - tijd: ~9 µs
 *
 *  // Bij het opzoeken van 'b07b7v' met 5000 producten
 *      - Gevonden producten: 1
 *      - tijd: ~15 µs
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

/**
 *  Deze functie zoekt alle producten die searchString als substring hebben, en sorteerd deze op basis van de korting
 *  Dit wordt gedaan door de searchString op te zoeken in de trie. Elke node heeft een lijst (QSet) van producten,
 *  hierdoor is het mogelijk om, zodra de laatste node van de searchString gevonden is, alle producten gesorteerd terug te geven.
 *
 *  Een woord opzoeken in een trie kan in O(k) tijd gedaan worden, waarbij k staat voor het aantal karakters in de searchString.
 *  Het sorteren wordt gedaan met std::partial_sort, we gebruiken deze functie om een bepaald aantal producten met de grootste korting vanvoor te zetten en te sorteren
 *  De rest van de array moet niet gesorteerd worden. partial_sort heeft een tijdscomplexiteit van O(n log(n)).
 *  Dit is hetzelfde als std::sort, maar hier moeten minder swaps gedaan worden omdat we het grootste deel ongesorteerd laten.
 *
 *  // Bij het opzoeken van 'b' met 5000 producten
 *      - Gevonden producten: 5000
 *      - tijd: ~15 ms
 *
 *  // Bij het opzoeken van 'b07b7v' met 5000 producten
 *      - Gevonden producten: 1
 *      - tijd: ~116 µs
 */
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
 * product opgeslagen.
 *
 * Het product wordt in elke node waar de string langskomt opgeslagen, op deze manier kan je het product vinden als het einde van de string mist.
 * Als je ook alle suffixen van de string in de trie zet, kan je dus een product vinden met eender welke substring.
 *
 * // Tijdcomplexiteit:
 *      - Inserten van woord in trie: O(k) -> k = #chars in string
 *      - Inserten van product in QSet = O(1)
 *
 * De totale tijdscomplexiteit van deze functie is dus O(k).
 *
 * // We hebben verschillende collecties getest voor het opslaan van de producten in de nodes:
 *      - QSet: ~12 ms
 *      - QSet met contains: ~14 ms
 *      - QVector: ~10 ms
 *
 * Hieruit blijkt dat de QVector iets sneller is dan de QSet, Het inserten is beide O(1), maar aangezien de QSet nog een hash moet generen kan het zijn
 * dat deze iets meer tijd nodig heeft. Om te zorgen dat alle producten maximaal één maal in een node zitten wordt er gebruik gemaakt van de contains() functie.
 * bij de QVector. Bij de QSet is dit niet nodig aangezien alle keys uniek moeten zijn.
 *
 * Na het plotten van de insert tijd voor de QVector en de QSet kunnen we het volgende besluiten:
 *  QVector is sneller bij minder producten (< 2000). Met meer producten blijft de insert tijd van QVector stijgen, terwijl
 *  de tijd van de Qset veel constanter blijft (met een lichte stijging). De hogere stijging van QVector zal waarschijnlijk komen
 *  doordat we gebruik maken van de contains() functie. Deze moet alle elementen in de vector afgaan.
 *
 * // Er is een verschil tussen de gemiddelde waardes bij het inserten van de eerste producten en de producten die later worden geinsert.
 *      - 0 tot 1000: ~12 ms
 *      - 1000 tot 4000: ~8 ms
 *      - >4000: begint weer te stijgen
 *
 * Een mogelijke verklaring hiervoor is dat er in het begin meer nodes moeten aangemaakt worden, bij de latere producten zijn deze al aangemaakt
 * waardoor het inserten minder tijd in beslag neemt.
 * Zodra er meer dan 4000 producten in de trie staan begint de insert tijd weer te stijgen, dit is ook het moment dat de RAM vol is. Het kan dus zijn dat
 * er tijd wordt verloren doordat het besturingssysteem de harde schrijf moet gebruiken in plaats van de RAM
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
        currentNode->products.insert(product);

        // Voor QVector:
        // if (!currentNode->products.contains(product)) {
        //     currentNode->products.push_back(product);
        // }
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
