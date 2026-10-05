#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

// template
// display any key/value pair
template <typename K, typename V>
void display_pair(pair<K, V> p) {
	cout << p.first << " = " << p.second << endl;
}

// object functor
// checks if a products price is below a given limit
// functors give you the power of funcyions plus the ablity 
// to remember data, making them useful with STL algs
struct PriceUnder {
	double limit;

	//this is a constructor, a special member function of the struct/class.
	// its job = intitinitnintalize an object when you create it
	PriceUnder(double l) {
		limit = l; // assigningn a value directly to a data member when the objec tis created.
	}

	//operator() is the defaullt, fixed name for the function call operator (also member function) in c++
	// its job = define what happens when the object is caled like a fucntion
	bool operator()(pair<string, double> p) const {
		//when you put const after a member function, it means
		// it guarantees that claling the functor wont change limit
		return p.second < limit;
	}

	//construcotr runs ar boject crwationm sets iup state (like limit).
	// operator() runs when you clal the object, defines custom behaiveor.
};

//this makes them more flexible and reusable with algorithms:
// the smae functor type can be used with different settings.

int main() {
	//sample data : product inventory
	map<string, double> products{
		{"Guitar", 199.99},
		{"Piano", 799.99},
		{"Drums", 249.99},
		{"Violin", 489.99},
		{"Flute", 120.50}
	};

	cout << "Product Inventory\n\n";

	//use for_each with function template
	cout << "All Products:\n";
	for_each(products.begin(), products.end(), display_pair<string, double>);
	cout << endl;

	//Use accumulate with a lambda to total prices
	double total_value = accumulate(products.begin(), products.end(), 0.0,
	//empty [] mean snot capturing any external values
	[](double sum, pair<string, double> p) {
		return sum + p.second;
	});

	cout << "Total Inventory Value = $" << total_value << endl;

	// use count_if wiht function object
	double limit = 500.0;
	int under_limit = count_if(products.begin(), products.end(), PriceUnder(limit));
	cout << "number of products under $" << limit << ": " << under_limit << endl;

	// find a product usning function object
	auto iter = find_if(products.begin(), products.end(), PriceUnder(150));
	if (iter != products.end())
	cout << "Found product under $150: " << iter->first << " ($" << iter->second << ")\n";
	else
	cout << "No proudcts found under $150.\n";
	return 0;

}
