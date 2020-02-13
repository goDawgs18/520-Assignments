#include "db.h"
#include "gtest/gtest.h"

namespace {

  TEST(DB, create_test_data) {
    DB db;

    db.create_test_data(5);
    std::cout << "start\n";
    for (int i = 0; i < 5; i++) {
      std::cout << "(" << NAME(db.find(i)) << ", " << MASS(db.find(i)) << ", "<< DISTANCE(db.find(i)) << "), ";
    }
    std::cout << "\nend";
  }  

  TEST(DB, search_name) {
        DB db;

        db.insert("earth", 1, 1)            
          .insert("mars", 0.11, 1.524)
          .insert("moon", 0.012, 1)
          .insert("exoplanet one", 1, 1054.4)
          .insert("jupiter", 318, 5.2);

        ASSERT_EQ(NAME(db.find_by_name("earth")), NAME(db.find(0)));

        try {
            db.find_by_name("krypton");  
            FAIL();
        } catch ( runtime_error e ) {
            ASSERT_STREQ(e.what(), "Could not find row by name");
        }  

    }  

    TEST(DB, addPlanetTwice) {
        DB db;

        db.insert("earth", 1, 1)            
          .insert("mars", 0.11, 1.524)
          .insert("moon", 0.012, 1)
          .insert("exoplanet one", 1, 1054.4)
          .insert("jupiter", 318, 5.2);

        ASSERT_EQ(NAME(db.find(0)), "earth");
        auto rows = db.where([](DB::Row row) { return  true; }); 
        try {
            db.insert("earth", 1, 1);  
            FAIL();
        } catch ( runtime_error e ) {
            ASSERT_STREQ(e.what(), "Name already exists");
        }  
        auto rows2 = db.where([](DB::Row row) { return  true; }); 
        ASSERT_EQ(rows.size(), rows2.size());
    }

    TEST(DB,Basics) {

        DB db;

        db.insert("earth", 1, 1)            
          .insert("mars", 0.11, 1.524)
          .insert("moon", 0.012, 1)
          .insert("exoplanet one", 1, 1054.4)
          .insert("jupiter", 318, 5.2);

        ASSERT_EQ(NAME(db.find(0)), "earth");

        auto rows = db.where([](DB::Row row) { return  MASS(row) < 1; }); 

        ASSERT_EQ(rows.size(), 2);

        try {
            db.drop(2)                        
              .find(2);  
            FAIL();
        } catch ( runtime_error e ) {
            ASSERT_STREQ(e.what(), "Could not find an entry with the given key");
        }     

    }

}