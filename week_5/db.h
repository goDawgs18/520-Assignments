#ifndef __DB_H
#define __DB_H

#include <string>
#include <tuple>
#include <map>
#include <vector>
#include <functional>

using namespace std;

#define KEY get<0>
#define NAME get<1>
#define MASS get<2>
#define DISTANCE get<3>

class DB {

  public:

    
    typedef tuple<int,string,double,double> Row;

    DB();
    DB &insert(const string, double, double);
    DB &drop(int);
    Row find(int) const;
    vector<Row> where(function<bool(const Row)> f) const;

    DB::Row find_by_name(const string name) const;
    // put n entries into the database with
    // custom name n, will just be a number because it doesn't say that isn't okay
    // mass should vary from 0.01 to 1000 and the distance from 0.1 to 10,000,000.
    DB &create_test_data(int n);

    int size() const;

    double accumulate(function<double(const Row)> f) const;
    double average_mass() const;
    double average_distance() const;
  private:

    typedef tuple<string,double,double> Value;
    Row to_row(int,const Value) const;
    map<int,Value> _data;
    int _next_key;

};

#endif