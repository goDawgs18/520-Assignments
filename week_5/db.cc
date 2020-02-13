#include <exception>
#include "db.h"
#include <iostream>
// #include <time.h>       /* time */
#include <cstdlib>

using namespace std;

DB::DB() : _next_key(0) {}

DB & DB::create_test_data(int n) {
    int name_index = 0;
    for (int i = 0; i < n; i++) {
        bool need_new_name = true;
        while (need_new_name) {
            try {
                auto t = find_by_name(std::to_string(name_index));
                name_index++;
            } catch (runtime_error e) {
                need_new_name = false;
            }
        }
        double random_mass_base = (double)rand()/RAND_MAX;
        int mass_times10 = random_mass_base * 10000000 * 10;
        double mass = (double)abs(mass_times10) / 10;
        double random_dist_base = (double)rand()/RAND_MAX;
        int dist_times100 = random_dist_base * 1000 * 100;
        double dist = (double)abs(dist_times100) / 100;
        insert(std::to_string(name_index), mass, dist);
    }

    return *this;
}

DB::Row DB::find_by_name(const string name) const {
    for (int i = 0; i < _next_key; i++) {
        if (NAME(find(i)) == name) {
            return find(i);
        }
    }
    throw runtime_error("Could not find row by name");
}

DB &DB::insert(const string name, double mass, double distance) {
    // Unsure how to pass a constant into lambda
    // probably better implementation here
    // auto same_name = [](DB::Row r, const string name) { return NAME(r) == name; };
    // if (where(same_name).size != 0 ) {
    //     throw runtime_error("Name already exists");
    // }

    for (int i = 0; i < _next_key; i++) {
        if (NAME(find(i)) == name) {
            throw runtime_error("Name already exists");
        }
    }

    int key = _next_key++;
    _data[key] = make_tuple(name, mass, distance);
    return *this;

}

DB &DB::drop(int key) {

    auto e = _data.find(key);

    if ( e != _data.end() ) {
        _data.erase (e);
    }

    return *this;
}

DB::Row DB::to_row(int key, const DB::Value value) const {
    return make_tuple(key, get<0>(value), get<1>(value), get<2>(value));
}

DB::Row DB::find(int key) const {

    auto e = _data.find(key);

    if ( e != _data.end() ) {
        return to_row(key,e->second);
    } else {
        throw runtime_error("Could not find an entry with the given key");
    }

}

vector<DB::Row> DB::where(function<bool(const DB::Row)> f) const {

    vector<Row> rows;

    for( auto [key, value] : _data ) {
        auto row = to_row(key,value);
        if ( f(row) == true ) {
            rows.push_back(row);
        }
    }

    return rows;

}

