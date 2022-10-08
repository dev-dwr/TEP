#include <iostream>
#include "main.h"
//alokacja statyczna ma miejsce kiedy deklarujemy zmienna
//Znak & oznacza referencję do obiektu/zmiennej. Tak więc zmienna &pcOther jest referencją
//do typu CAllocTest. Referencja to wskaźnik

void v_alloc_table_fill_34(int iSize) {
    if (iSize < 0) {
        std::cout << "Size needs to be a positive number" << std::endl;
        return;
    }
    int *array;
    array = new int[iSize];

    for (int i = 0; i < iSize; i++) {
        array[i] = DEFAULT_34_NUMBER;
    }

    for (int i = 0; i < iSize; i++) {
        std::cout << array[i] << std::endl;
    }

    delete[] array;
}

bool b_alloc_table_2dim(int **&piTable, int iSizeX, int iSizeY) {
    if (iSizeX < 0) {
        std::cout << "row number must be positive" << std::endl;
        return false;
    }
    if (iSizeY < 0) {
        std::cout << "column number must be positive" << std::endl;
        return false;
    }
    if (piTable == NULL) {
        std::cout << " pi_table null value passed" << std::endl;
        return false;
    }

    piTable = new int *[iSizeX]; //allocate row
    for (int i = 0; i < iSizeX; i++) {
        piTable[i] = new int[iSizeY]; //allocate column
    }

    return true;
}

void allocate_array_data(int **&piTable, int iSizeX, int iSizeY) {
    for (int i = 0; i < iSizeX; i++) {
        for (int j = 0; j < iSizeY; j++) {
            piTable[i][j] = 5;
        }
    }
}

bool b_dealloc_table_2_dim(int **piTable, int iSizeX) {
    if (iSizeX != I_SIZE_X) {
        std::cout << "cannot deallocate array wrong number row passed" << std::endl;
        return false;
    }
    if (piTable == NULL) {
        std::cout << "null value passed" << std::endl;
        return false;
    }
    //delete piTable;. Skasuje ono wyłącznie tablicę wskaźników
    for (int i = 0; i < iSizeX; i++) {
        delete[] piTable[i]; //delete all rows in every column
    }

    delete[] piTable; // delete columns
    return true;
}

void display_array(int **&piTable, int iSizeX, int iSizeY) {
    for (int i = 0; i < iSizeX; i++) {
        for (int j = 0; j < iSizeY; j++) {
            std::cout << piTable[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

class CTable {
private:
    std::string s_name;
    int *array;
    int tableSize;
public:
    CTable() {
        s_name = DEFAULT_S_NAME;
        std::cout << "bezp: " + s_name << std::endl;
        array = new int[DEFAULT_ARRAY_LENGTH];
    }

    CTable(std::string sName, int iTableLen) {
        if (sName.empty()) {
            std::cout << "enter non empty string" << std::endl;
            return;
        }
        if (iTableLen < 0) {
            std::cout << "table size must be positive" << std::endl;
            return;
        }
        tableSize = iTableLen;
        s_name = sName;
        std::cout << "parameter: " + s_name << std::endl;
        array = new int[iTableLen];
    }

    CTable(const CTable &pcOther) {
        s_name = pcOther.s_name + "_copy";
        tableSize = pcOther.tableSize;
        std::cout << "copy: " + s_name << std::endl;
        array = pcOther.array;
    }

    ~CTable() {
        std::cout << "usuwam: " + s_name << std::endl;
    }

    void setName(std::string sName) {
        if (sName.empty()) {
            std::cout << "enter non empty string" << std::endl;
            return;
        }
        s_name = sName;
    }

    bool bSetNewSize(int iTableLen) {
        if (iTableLen < 0) {
            std::cout << "we did not changed array size, reason: negative num" << std::endl;
            return false;
        }
        array = new int[iTableLen];
        tableSize = iTableLen;
        std::cout << "we changed array size" << std::endl;
        return true;
    }

    CTable *pcClone() {
        CTable *clone;
        clone = new CTable(s_name, tableSize);
        return clone;
    }

    std::string print() {
        std::cout << tableSize << std::endl;
    }
};

std::string bool_to_string_converter(const bool b) {
    return b ? "true" : "false";
}

void v_mod_tab(CTable *pc_new_tab, int iNewSize) {
    pc_new_tab->bSetNewSize(iNewSize);
    pc_new_tab->print();
}

void v_mod_tab(CTable c_tab, int iNewSize) {
    c_tab.bSetNewSize(iNewSize);
    c_tab.print();
}

int main() {
    std::cout << "TASK 1" << std::endl;
    int iSize = 2;
    v_alloc_table_fill_34(iSize);
    std::cout << "\n" << std::endl;

    std::cout << "TASK 2" << std::endl;
    int **pi_table; //    int **pi_table = new int*[iSizeX]; //    display_array(pi_table, I_SIZE_X, I_SIZE_Y);
    bool alloc_result = b_alloc_table_2dim(pi_table, I_SIZE_X, I_SIZE_Y);
    std::cout << "alloc result: " << std::endl;
    std::cout << bool_to_string_converter(alloc_result) << std::endl;
    allocate_array_data(pi_table, I_SIZE_X, I_SIZE_Y);
    std::cout << "\n" << std::endl;

    std::cout << "TASK 3" << std::endl;
    bool dealloc_result = b_dealloc_table_2_dim(pi_table, I_SIZE_X);
    std::cout << "dealloc result: " << std::endl;
    std::cout << bool_to_string_converter(dealloc_result) << std::endl;
    std::cout << "\n" << std::endl;


    std::cout << "TASK 4" << std::endl;
    CTable staticTable;

    CTable *cloneCTable;
    cloneCTable = new CTable(staticTable);
    delete cloneCTable;

    CTable *nonParameterConstr;
    nonParameterConstr = new CTable();
    delete nonParameterConstr;

    CTable *parameterConstr;
    parameterConstr = new CTable("constr", 2);
    delete parameterConstr;


    
    std::cout << "\n" << std::endl;
    int iNewSize = 4;
    CTable c_tab; //static allo statyczna wywoluje konstruktor i dekonstruktor
    CTable *pc_new_tab; // dynamic allo wywoluje konstruktor ale dekonstruktor wtedy gdy damy delete pc_new_tab;
    pc_new_tab = c_tab.pcClone();
    delete pc_new_tab;
    v_mod_tab(c_tab, iNewSize); //zmodyfikuje
//    v_mod_tab(*pc_new_tab, iNewSize); //nie zmodyfikuje

    return 0;
}


