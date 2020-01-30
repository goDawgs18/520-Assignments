#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
// // #include <stdlib.h>
// // #include <string.h>
// // #include <assert.h>
#include <cfloat>
// #include <cstddef>

// #include <cstring>
// #include <cstdio>
// #include <cstddef>


/* private functions *********************************************************/

/* Position in the buffer of the array element at position index */
static int index_to_offset ( const DynamicArray * da, int index ) {
    return index + da->origin;
}

/* Position of the element at buffer position 'offset' */
static int offset_to_index ( const DynamicArray * da, int offset ) {
    return offset - da->origin;
}

/* Non-zero if and only if offset lies ouside the buffer */
static int out_of_buffer ( DynamicArray * da, int offset ) {
    return offset < 0 || offset >= da->capacity;
}

/* Makes a new buffer that is twice the size of the old buffer,
   copies the old information into the new buffer, and deletes
   the old buffer */
static void extend_buffer ( DynamicArray * da ) {

    double * temp = (double *) calloc ( 2 * da->capacity, sizeof(double) );
    int new_origin = da->capacity - (da->end - da->origin)/2,
           new_end = new_origin + (da->end - da->origin);

    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        temp[new_origin+i] = DynamicArray_get(da,i);
    }

    free(da->buffer);
    da->buffer = temp;

    da->capacity = 2 * da->capacity;
    da->origin = new_origin;
    da->end = new_end;

    return;

}

/* public functions **********************************************************/

DynamicArray * DynamicArray_new(void) {
    DynamicArray * da = (DynamicArray *) malloc(sizeof(DynamicArray));
    da->capacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;    
    da->buffer = (double *) calloc ( da->capacity, sizeof(double) ); 
    da->origin = da->capacity / 2;
    da->end = da->origin;
    return da;
}

void DynamicArray_destroy(DynamicArray * da) {
    free(da->buffer);
    da->buffer = NULL;
    return;
}

int DynamicArray_size(const DynamicArray * da) {
    assert(da->buffer != NULL);
    return da->end - da->origin;
}

char * DynamicArray_to_string(const DynamicArray * da) {
    assert(da->buffer != NULL);
    char * str = (char *) calloc (20,DynamicArray_size(da)),
         temp[20];
    int j = 1;
    str[0] = '[';
    for ( int i=0; i < DynamicArray_size(da); i++ ) {
        if ( DynamicArray_get(da,i) == 0 ) {
            snprintf ( temp, 20, "0" );
        } else {
            snprintf ( temp, 20, "%.5lf", DynamicArray_get(da,i) ); 
        }
        if ( i < DynamicArray_size(da) - 1 ) {
            sprintf( str + j, "%s,", temp);
            j += strlen(temp) + 1;
        } else {
            sprintf( str + j, "%s", temp);
            j += strlen(temp);
        }

    }
    str[j] = ']';
    return str;
}

void DynamicArray_print_debug_info(const DynamicArray * da) {

    char * s = DynamicArray_to_string(da);
    printf ( "  %s\n", s);
    printf ( "  capacity: %d\n  origin: %d\n  end: %d\n  size: %d\n\n",
      da->capacity, 
      da->origin, 
      da->end,
      DynamicArray_size(da));

    free(s);

}

void DynamicArray_set(DynamicArray * da, int index, double value) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    while ( out_of_buffer(da, index_to_offset(da, index) ) ) {
        extend_buffer(da);
    }
    da->buffer[index_to_offset(da, index)] = value;
    if ( index >= DynamicArray_size(da) ) {
        da->end = index_to_offset(da,index+1);
    }

}

double DynamicArray_get(const DynamicArray * da, int index) {
    assert(da->buffer != NULL);
    assert ( index >= 0 );
    if ( index >= DynamicArray_size(da) ) {
        return 0;
    } else {
        return da->buffer[index_to_offset(da,index)];
    }
}

void DynamicArray_push(DynamicArray * da, double value ) {
    DynamicArray_set(da, DynamicArray_size(da), value );
}

void DynamicArray_push_front(DynamicArray * da, double value) {
    assert(da->buffer != NULL);
    while ( da->origin == 0 ) {
        extend_buffer(da);
    }
    da->origin--;
    DynamicArray_set(da,0,value);
}

double DynamicArray_pop(DynamicArray * da) {
    double value = DynamicArray_last(da);
    DynamicArray_set(da, DynamicArray_size(da)-1, 0.0);
    da->end--;
    return value;
}

double DynamicArray_pop_front(DynamicArray * da) {
    double value = DynamicArray_first(da);
    da->origin++;
    return value;    
}

double DynamicArray_first ( const DynamicArray * da ) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, 0);
    return value; 
}

double DynamicArray_last ( const DynamicArray * da ) {
    assert(DynamicArray_size(da) > 0);
    double value = DynamicArray_get(da, DynamicArray_size(da)-1);
    return value; 
}

DynamicArray * DynamicArray_map(const DynamicArray * da, double (*f) (double)) {
    assert(da->buffer != NULL);
    DynamicArray * result = DynamicArray_copy(da);
    for ( int i=0; i<DynamicArray_size(da); i++ ) {
        DynamicArray_set(result, i, f(DynamicArray_get(result, i)));
    }
    return result;
}

DynamicArray * DynamicArray_subarray(DynamicArray * da, int a, int b) {

  assert(da->buffer != NULL);
  assert(b >= a);

  DynamicArray * result = DynamicArray_new();

  for (int i=a; i<b; i++) {
      DynamicArray_push(result,DynamicArray_get(da, i));
  }

  return result;

}

double DynamicArray_min ( const DynamicArray * da ) {
    assert(DynamicArray_size(da) > 0);
    double min = DBL_MAX;
    int size = DynamicArray_size(da);
    for (int i = 0; i < size; i++) {
        if (DynamicArray_get(da, i) < min) {
            min = DynamicArray_get(da, i);
        }
    }
    return min;
}

double DynamicArray_max ( const DynamicArray * da ) {
    assert(DynamicArray_size(da) > 0);
    double max = -DBL_MAX;
    int size = DynamicArray_size(da);
    for (int i = 0; i < size; i++) {
        if (DynamicArray_get(da, i) > max) {
            max = DynamicArray_get(da, i);
        }
    }
    return max;
}

double DynamicArray_mean ( const DynamicArray * da ) {
    assert(DynamicArray_size(da) > 0);
    return DynamicArray_sum(da)/DynamicArray_size(da);
}

double DynamicArray_median ( const DynamicArray * da ) {
    assert(DynamicArray_size(da) > 0);
    DynamicArray * oth = DynamicArray_copy(da);
    int size = DynamicArray_size(da);
    DynamicArray_sort(oth);
    if (size % 2 == 0) {
        double median = (DynamicArray_get(oth, size / 2 - 1) + 
                DynamicArray_get(oth, size / 2)) / 2; 
        DynamicArray_destroy(oth);
        return median; 
    } else {
        double median = DynamicArray_get(oth, size/2); 
        DynamicArray_destroy(oth);
        return median;
    }
}

DynamicArray * DynamicArray_sort( DynamicArray * b ) {
    for (int i = 0; i < DynamicArray_size(b) - 1; i++) {
        if (DynamicArray_get(b, i) > DynamicArray_get(b, i + 1)) {
            for (int q = i; q < DynamicArray_size(b); q++) {
                if (DynamicArray_get(b, q) > DynamicArray_get(b, q + 1)) {
                    double tmp = DynamicArray_get(b, q);
                    DynamicArray_set(b, q, DynamicArray_get(b, q + 1));
                    DynamicArray_set(b, q + 1, tmp);
                }
            }
        }
    }
    return b;
}

double DynamicArray_sum ( const DynamicArray * da ) {
    double sum = 0.0;
    int size = DynamicArray_size(da);
    for (int i = 0; i < size; i++) {
        sum += DynamicArray_get(da, i);
    }
    return sum;
}

DynamicArray * DynamicArray_copy ( const DynamicArray * da ) {
    DynamicArray * oth = DynamicArray_new();
    int size = DynamicArray_size(da);
    for (int i = 0; i < size; i++) {
        DynamicArray_push(oth, DynamicArray_get(da, i));
    }
    return oth;
}

DynamicArray * DynamicArray_range ( double a, double b, double step) {
    DynamicArray * g = DynamicArray_new();
    double val = a;
    if ( b < a && step < 0) {
        while (val >= b) {
            DynamicArray_push(g, val);
            val += step;
        }
    } else {
        while (val <= b) {
            DynamicArray_push(g, val);
            val += step;
        }
    }
    return g;
}

void DynamicArray_add_on ( const DynamicArray * a,  DynamicArray * b ) {
    for (int i = 0; i < DynamicArray_size(a); i++) {
        DynamicArray_get(a, i);
        DynamicArray_push(b, DynamicArray_get(a, i));
    }
}

DynamicArray * DynamicArray_concat ( const DynamicArray * a, const DynamicArray * b ) {
    DynamicArray * g = DynamicArray_new();
    DynamicArray_add_on(a, g);
    DynamicArray_add_on(b, g);
    return g;
}

DynamicArray * DynamicArray_take ( DynamicArray * a, int n ) {
    DynamicArray * da = DynamicArray_new();
    if (n < 0) {
        for (int i = 0; i < n * -1; i++) {
            if (i < DynamicArray_size(a)) {
                DynamicArray_push_front(da, DynamicArray_get(a, 
                        DynamicArray_size(a) -1 - i));
            } else {
                DynamicArray_push(da, 0);
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            if (i < DynamicArray_size(a)) {
                DynamicArray_push(da, DynamicArray_get(a, i));
            } else {
                DynamicArray_push(da, 0);
            }
        }
    }
    return da;
}