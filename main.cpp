#include <iostream>
#include "main.h"

//zadanie 1
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

//zadanie 2
bool b_alloc_table_2dim(int ***piTable, int iSizeX, int iSizeY) {
    if (iSizeX < 0) {
        std::cout << "row number must be positive" << std::endl;
        return false;
    }
    if (iSizeY < 0) {
        std::cout << "column number must be positive" << std::endl;
        return false;
    }

    *piTable = new int *[iSizeX]; //allocate row
    for (int i = 0; i < iSizeX; i++) {
        (*piTable)[i] = new int[iSizeY]; //allocate column
    }

    return true;
}

void allocate_array_data(int **piTable, int iSizeX, int iSizeY) {
    for (int i = 0; i < iSizeX; i++) {
        for (int j = 0; j < iSizeY; j++) {
            piTable[i][j] = 5;
        }
    }
}

//zadnie 3
bool b_dealloc_table_2_dim(int ***piTable, int iSizeX, int iSizeY) {
    if (iSizeY < 0){
        std::cout << "cannot deallocate array wrong number column passed" << std::endl;
        return false;
    }
    if (iSizeX < 0 ) {
        std::cout << "cannot deallocate array wrong number row passed" << std::endl;
        return false;
    }

    //delete piTable; Skasuje ono wyłącznie tablicę wskaźników
    for (int i = 0; i < iSizeX; i++) {
        delete[] (*piTable)[i]; //delete all rows in every column
    }

    delete[] *piTable; // delete columns
    return true;
}

//zadanie 4
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

    CTable(const CTable &pcOther) { // kopiujacy
        s_name = pcOther.s_name + "_copy";
        tableSize = pcOther.tableSize;
        std::cout << "copy: " + s_name << std::endl;
        array = pcOther.array;
    }

    ~CTable() {
        delete array;
        tableSize = 0;
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
        std::cout << "we changed array size bSetNewSize" << std::endl;
        return true;
    }

    CTable *pcClone() {
        CTable *clone;
        clone = new CTable(s_name, tableSize);
        return clone;
    }

    std::string printTableSize() {
        std::cout << "table size = "<< tableSize << std::endl;
    }
};

std::string bool_to_string_converter(const bool b) {
    return b ? "true" : "false";
}

void v_mod_tab(CTable *pc_new_tab, int iNewSize) {
    pc_new_tab->bSetNewSize(iNewSize);
}

void v_mod_tab(CTable c_tab, int iNewSize) {
    c_tab.bSetNewSize(iNewSize);
}
int main() {
    std::cout << "TASK 1" << std::endl;
    int iSize = 3;
    v_alloc_table_fill_34(iSize);
    std::cout << "\n" << std::endl;

    std::cout << "TASK 2" << std::endl;
    int ***pi_table; //allocate_array_data(pi_table, I_SIZE_Y, I_SIZE_X);
    bool alloc_result = b_alloc_table_2dim(pi_table, I_SIZE_Y, I_SIZE_X);
    std::cout << "alloc result: " << std::endl;
    std::cout << bool_to_string_converter(alloc_result) << std::endl;
    std::cout << "\n" << std::endl;

    std::cout << "TASK 3" << std::endl;
    bool dealloc_result = b_dealloc_table_2_dim(pi_table, I_SIZE_Y, I_SIZE_X);
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
    std::cout << "procedura 1:" << std::endl;
    CTable *table1;
    table1 = new CTable();
    v_mod_tab(*table1, iNewSize); //nie zmodyfikuje, utworzy kopie obiektu
    table1->printTableSize();

    std::cout << "procedura 2:" << std::endl;
    CTable *table2;
    table2 = new CTable();
    v_mod_tab(table2, iNewSize); //zmodyfikuje nie utowrzy kopii obiektu
    table2->printTableSize();

    return 0;
}





//    CTable c_tab; //static allo statyczna wywoluje konstruktor i dekonstruktor
//    CTable *pc_new_tab; // dynamic allo wywoluje konstruktor ale dekonstruktor wtedy gdy damy delete pc_new_tab;
//    pc_new_tab = c_tab.pcClone();
//    delete pc_new_tab;
//    std::cout << "\n" << std::endl;
//    delete pc_new_tab;
