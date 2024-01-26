/*
Apache License
Version 2.0, January 2004
http://www.apache.org/licenses/

Copyright  [Aditya Saharan]

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

enum Genre
{
    Fiction,
    NonFiction,
    Mystery,
    SciFi,
    Romance,
    History,
    Technology,
    Indian,
    Hindi,
    Action,
    Anime,
    Science,
    Horror,
    Fiction,
    Fantasy,
    // Add more genres as needed
};

string genreToString(Genre genre)
{
    switch (genre)
    {
    case Fiction:
        return "Fiction";
    case NonFiction:
        return "Non-Fiction";
    case Mystery:
        return "Mystery";
    case SciFi:
        return "Science Fiction";
    case Romance:
        return "Romance";
    case History:
        return "History";
    case Technology:
        return "Technology";
    case Indian:
        return "Indian";
    case Hindi:
        return "Hindi";
    case Action:
        return "Action";
    case Anime:
        return "Anime";
    case Science:
        return "Science";
    case Horror:
        return "Horror";

    case Fantasy:
        return "Fantasy";

    // Add more cases as needed
    default:
        return "Unknown";
    }
}

class Book
{
private:
    string title;
    string author;
    int year;
    double price;
    int stock;
    Genre genre;

public:
    // Constructor
    Book(string t, string a, int y, double p, int s, Genre g) : title(t), author(a), year(y), price(p), stock(s), genre(g) {}

    // Getter methods
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }
    Genre getGenre() const { return genre; }

    // Setter methods
    void setStock(int s) { stock = s; }

    // Display book details
    void display() const
    {
        cout << "Title: " << title << "\nAuthor: " << author << "\nYear: " << year
             << "\nPrice: $" << fixed << setprecision(2) << price << "\nStock: " << stock
             << "\nGenre: " << genreToString(genre) << "\n\n";
    }
};

class Bookstore
{
private:
    vector<Book> books;

public:
    // Add a book to the bookstore
    void addBook(const Book &book)
    {
        books.push_back(book);
    }

    // Display all books in the bookstore
    void displayBooks() const
    {
        for (const auto &book : books)
        {
            book.display();
        }
    }

    // Find a book by title
    Book *findBookByTitle(const string &title)
    {
        auto it = find_if(books.begin(), books.end(), [&title](const Book &book)
                          { return book.getTitle() == title; });

        if (it != books.end())
        {
            return &(*it);
        }
        else
        {
            return nullptr;
        }
    }

    // Display books by genre
    void displayBooksByGenre(Genre genre) const
    {
        vector<Book> matchingBooks;

        for (const auto &book : books)
        {
            if (book.getGenre() == genre)
            {
                matchingBooks.push_back(book);
            }
        }

        if (!matchingBooks.empty())
        {
            cout << "Books in " << genreToString(genre) << " genre:\n";
            for (const auto &book : matchingBooks)
            {
                book.display();
            }
        }
        else
        {
            cout << "No books found in " << genreToString(genre) << " genre.\n";
        }
    }
    // ... (previous functions remain unchanged)

    // Display all authors in the bookstore
    void displayAuthors() const
    {
        vector<string> authors;

        for (const auto &book : books)
        {
            authors.push_back(book.getAuthor());
        }

        // Remove duplicates
        sort(authors.begin(), authors.end());
        authors.erase(unique(authors.begin(), authors.end()), authors.end());

        // Display authors
        cout << "Authors:\n";
        for (const auto &author : authors)
        {
            cout << author << endl;
        }
    }

    // Display total number of books in the bookstore
    void displayTotalBooks() const
    {
        cout << "Total number of books: " << books.size() << "\n";
    }

    // Buy a book from the bookstore
    void buyBook(const string &title, int quantity)
    {
        Book *foundBook = findBookByTitle(title);

        if (foundBook != nullptr)
        {
            if (quantity > 0 && quantity <= foundBook->getStock())
            {
                foundBook->setStock(foundBook->getStock() - quantity);
                cout << "Successfully bought " << quantity << " copies of \"" << title << "\".\n";
            }
            else
            {
                cout << "Invalid quantity. Please enter a valid quantity within stock limit.\n";
            }
        }
        else
        {
            cout << "Book not found. Cannot complete the purchase.\n";
        }
    }

    // Search for books in stock based on a keyword
    void searchInStock(const string &keyword) const
    {
        vector<Book> matchingBooks;

        for (const auto &book : books)
        {
            if (book.getStock() > 0 && (book.getTitle().find(keyword) != string::npos ||
                                        book.getAuthor().find(keyword) != string::npos))
            {
                matchingBooks.push_back(book);
            }
        }

        if (!matchingBooks.empty())
        {
            cout << "Matching books in stock:\n";
            for (const auto &book : matchingBooks)
            {
                book.display();
            }
        }
        else
        {
            cout << "No matching books found in stock.\n";
        }
    }

    // Edit details of a book
    void editBookDetails(const string &title, const string &newAuthor, int newYear, double newPrice, int newStock, int setYear, int setPrice)
    {
        Book *foundBook = findBookByTitle(title);

        if (foundBook != nullptr)
        {
            foundBook->setStock(newStock);
            foundBook->setStock(newStock);
            // foundBook->setYear(newYear);
            // foundBook->setPrice(newPrice);

            cout << "Book details updated successfully.\n";
        }
        else
        {
            cout << "Book not found. Cannot edit details.\n";
        }
    }
};

// Function to display the menu
void displayMenu()
{
    cout << "1. Enter new book\n";
    cout << "2. Buy book\n";
    cout << "3. Search in stock\n";
    cout << "4. Search for a book\n";
    cout << "5. Edit book details\n";
    cout << "6. Display all books\n";
    cout << "7. Display books by genre\n";
    cout << "8. Display all authors\n";
    cout << "9. Display all genres\n";
    cout << "10.Display total number of books\n";
    cout << "11.Exit\n";
}

int main()
{
    Bookstore bookstore;

    // Adding sample books
    Book book1("The Great Gatsby", "F. Scott Fitzgerald", 1925, 12.99, 50, Fiction);
    Book book2("To Kill a Mockingbird", "Harper Lee", 1960, 14.99, 30, Mystery);
    Book book3("1984", "George Orwell", 1949, 10.50, 40, SciFi);
    Book book4("Pride and Prejudice", "Jane Austen", 1813, 9.99, 20, Romance);
    Book book5("The History of Time", "Stephen Hawking", 1988, 15.50, 15, History);
    Book book6("The Code Book", "Simon Singh", 1999, 18.75, 25, Technology);
    Book book7("Chanakya's Chant", "Ashwin Sanghi", 2010, 11.25, 35, Indian);
    Book book8("Madhushala", "Harivansh Rai Bachchan", 1935, 8.99, 40, Hindi);
    Book book9("The Catcher in the Rye", "J.D. Salinger", 1951, 11.25, 30, Fiction);
    Book book10("The Da Vinci Code", "Dan Brown", 2003, 14.99, 25, Mystery);
    Book book11("Dune", "Frank Herbert", 1965, 13.50, 35, SciFi);
    Book book12("Wuthering Heights", "Emily Brontë", 1847, 10.99, 18, Romance);
    Book book13("A Brief History of Time", "Stephen Hawking", 1988, 16.75, 20, Science);
    Book book14("Clean Code", "Robert C. Martin", 2008, 32.99, 15, Technology);
    Book book15("Design Patterns", "Erich Gamma", 1994, 28.50, 20, Technology);
    Book book16("Introduction to Algorithms", "Thomas H. Cormen", 1990, 45.00, 12, Technology);
    Book book17("Kamasutra", "Vatsyayana", 200, 9.99, 30, Science);
    Book book18("Nirmala", "Premchand", 1925, 7.50, 25, Indian);
    Book book19("Raj Kahini", "Abanindranath Tagore", 1909, 12.99, 22, History);
    Book book20("C++ Programming", "Bjarne Stroustrup", 1985, 24.99, 10, Technology);
    Book book21("The Silent Patient", "Alex Michaelides", 2019, 20.99, 18, Mystery);
    Book book22("Where the Crawdads Sing", "Delia Owens", 2018, 24.50, 25, Fiction);
    Book book23("Educated", "Tara Westover", 2018, 16.75, 30, NonFiction);
    Book book24("The Testaments", "Margaret Atwood", 2019, 22.99, 22, SciFi);
    Book book25("Circe", "Madeline Miller", 2018, 18.50, 20, Fantasy);
    Book book26("The Water Dancer", "Ta-Nehisi Coates", 2019, 19.25, 28, History);
    Book book27("Sapiens: A Brief History of Humankind", "Yuval Noah Harari", 2014, 15.99, 35, NonFiction);
    Book book28("The Outsider", "Stephen King", 2018, 17.50, 15, Horror);
    Book book29("The Institute", "Stephen King", 2019, 21.00, 18, Horror);
    Book book30("Becoming", "Michelle Obama", 2018, 25.99, 30, NonFiction);
    Book book31("The Silent Patient", "Alex Michaelides", 2019, 20.99, 18, Mystery);
    Book book32("Where the Crawdads Sing", "Delia Owens", 2018, 24.50, 25, Fiction);
    Book book33("Educated", "Tara Westover", 2018, 16.75, 30, NonFiction);
    Book book34("The Testaments", "Margaret Atwood", 2019, 22.99, 22, SciFi);
    Book book35("Circe", "Madeline Miller", 2018, 18.50, 20, Fantasy);
    Book book36("The Water Dancer", "Ta-Nehisi Coates", 2019, 19.25, 28, History);
    Book book37("Sapiens: A Brief History of Humankind", "Yuval Noah Harari", 2014, 15.99, 35, NonFiction);
    Book book38("The Outsider", "Stephen King", 2018, 17.50, 15, Horror);
    Book book39("The Institute", "Stephen King", 2019, 21.00, 18, Horror);
    Book book40("Becoming", "Michelle Obama", 2018, 25.99, 30, NonFiction);

    // Add more sample books as needed

    bookstore.addBook(book1);
    bookstore.addBook(book2);
    bookstore.addBook(book3);
    bookstore.addBook(book4);
    bookstore.addBook(book5);
    bookstore.addBook(book6);
    bookstore.addBook(book7);
    bookstore.addBook(book8);
    bookstore.addBook(book9);
    bookstore.addBook(book10);
    bookstore.addBook(book11);
    bookstore.addBook(book12);
    bookstore.addBook(book13);
    bookstore.addBook(book14);
    bookstore.addBook(book15);
    bookstore.addBook(book16);
    bookstore.addBook(book17);
    bookstore.addBook(book18);
    bookstore.addBook(book19);
    bookstore.addBook(book20);
    bookstore.addBook(book21);
    bookstore.addBook(book22);
    bookstore.addBook(book23);
    bookstore.addBook(book24);
    bookstore.addBook(book25);
    bookstore.addBook(book26);
    bookstore.addBook(book27);
    bookstore.addBook(book28);
    bookstore.addBook(book29);
    bookstore.addBook(book30);
    bookstore.addBook(book31);
    bookstore.addBook(book32);
    bookstore.addBook(book33);
    bookstore.addBook(book34);
    bookstore.addBook(book35);
    bookstore.addBook(book36);
    bookstore.addBook(book37);
    bookstore.addBook(book38);
    bookstore.addBook(book39);
    bookstore.addBook(book40);

    // Add more books as needed

    while (true)
    {
        displayMenu();

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            // ... (previous cases remain unchanged)

        case 1:
        {
            // Enter new book
            string title, author;
            int year, stock;
            double price;
            int genreChoice;

            cout << "Enter book details:\n";
            cout << "Title: ";
            cin.ignore(); // Ignore newline character in the buffer
            getline(cin, title);

            cout << "Author: ";
            getline(cin, author);

            cout << "Year: ";
            cin >> year;

            cout << "Price: $";
            cin >> price;

            cout << "Stock: ";
            cin >> stock;

            cout << "Enter genre (as a number):\n";
            cout << "1. Fiction\n2. Non-Fiction\n3. Mystery\n4. Sci-Fi\n5. Romance\n"
                    "6. History\n7. Technology\n8. Indian\n9. Hindi\n10. Action\n"
                    "11. Anime\n";
            cin >> genreChoice;

            Genre selectedGenre = static_cast<Genre>(genreChoice - 1);
            Book newBook(title, author, year, price, stock, selectedGenre);
            bookstore.addBook(newBook);
            cout << "Book added successfully!\n";
            break;
        }

        case 2:
        {
            // Buy book
            string title;
            int quantity;

            cout << "Enter the title of the book you want to buy: ";
            cin.ignore(); // Ignore newline character in the buffer
            getline(cin, title);

            cout << "Enter the quantity: ";
            cin >> quantity;

            bookstore.buyBook(title, quantity);
            break;
        }

        case 3:
        {
            // Search in stock
            string keyword;

            cout << "Enter a keyword to search in stock: ";
            cin.ignore(); // Ignore newline character in the buffer
            getline(cin, keyword);

            bookstore.searchInStock(keyword);
            break;
        }

        case 4:
        {
            // Search for a book
            string searchTitle;
            cout << "Enter the title to search: ";
            cin.ignore(); // Ignore newline character in the buffer
            getline(cin, searchTitle);

            Book *foundBook = bookstore.findBookByTitle(searchTitle);

            if (foundBook != nullptr)
            {
                cout << "Book found:\n";
                foundBook->display();
            }
            else
            {
                cout << "Book not found.\n";
            }

            break;
        }
        case 5:
        {
            // Edit book details
            string title, newAuthor;
            int newYear, newStock;
            double newPrice;

            cout << "Enter the title of the book to edit: ";
            cin.ignore(); // Ignore newline character in the buffer
            getline(cin, title);

            cout << "Enter new author: ";
            getline(cin, newAuthor);

            cout << "Enter new year: ";
            cin >> newYear;

            cout << "Enter new price: $";
            cin >> newPrice;

            cout << "Enter new stock: ";
            cin >> newStock;

            // Ignore newline character after reading newStock
            cin.ignore();

            // Assuming setYear and setPrice are not needed
            bookstore.editBookDetails(title, newAuthor, newYear, newPrice, newStock, newYear, newPrice);
            break;
        }

        case 6:
            cout << "All Books:\n";
            bookstore.displayBooks();
            break;

        case 7:
        {
            // Display books by genre
            int genreChoice;
            cout << "Enter genre (as a number):\n";
            cout << "1. Fiction\n2. Non-Fiction\n3. Mystery\n4. Sci-Fi\n5. Romance\n"
                    "6. History\n7. Technology\n8. Indian\n9. Hindi\n10. Action\n"
                    "11. Anime\n";
            cin >> genreChoice;

            Genre selectedGenre = static_cast<Genre>(genreChoice - 1);
            bookstore.displayBooksByGenre(selectedGenre);
            break;
        }

        case 8:
            // Display all authors
            bookstore.displayAuthors();
            break;

            // case 9:
            //                 // Display all genres
            //                 bookstore.displayGenres();
            //                 break;

        case 10:
            // Display total number of books
            bookstore.displayTotalBooks();
            break;

        case 11:
            cout << "Exiting the program. Goodbye!\n";
            return 0;
        }
    }

    return 0;
}
