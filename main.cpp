#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>

// Dominik Ficek

using namespace std;

/**
* Struktura danych studenta.
**/
struct Student{
	string imie;
	string nazwisko;
	string nrAlbumu;
	string ocena;
	string dataWpisu;
};

/**
* Struktura danych przedmiotu.
**/
struct Przedmiot{
	string nazwa;
	string prowadzacy;
};

/**
* Funkcja odczytuj¹ca z pliku nazwy przedmiotu i prowadz¹cego
* i wpisanie do tablicy.
*
* @param file1 plik z danymi przedmiotu
* @param prz tablica danych o przedmiocie
**/
void readPrzedmiot(ifstream &file1, Przedmiot &prz){
	
	string line;
	getline(file1, line);
	prz.nazwa =  line;
	getline(file1, line);
	prz.prowadzacy = line;
}

/**
* Funkcja na wpisanie z pliku imienia, nazwiska, nr albumu, ceny, daty wpisu do tablicy.
*
* @param file1 plik z danymi przedmiotu
* @parma stu tablica danych jendego studenta
**/
void readStudent(ifstream &file1, Student &stu){
	
	file1 >> stu.imie >> stu.nazwisko >> stu.nrAlbumu >> stu.ocena >> stu.dataWpisu;
}

/**
* Fucnkcja na wpisanie danych studenta do tablicy dynamicznej.
*
* @param flie1 plik z danymi przedmiotu
* @param stuTab tablica dynamiczna do zapisania danych
* @param numOfStudent liczba studentów w danym pliku 
**/
void readStuTab(ifstream &file1, Student *stuTab, const int numOfStudent){
	
	for(int i=0; i<numOfStudent; i++){
		readStudent(file1, stuTab[i]);
	}
}

/**
* Funkcja zliczaj¹ca iloœæ studentów w pliku.
*
* @param file1Path œcie¿ka do pliku z daymi przedmiotu
* @param numOfStudent liczba studentów w danym pliku
* @return 1 jeœli nie uda³o siê otworzyæ pliku, 0 jeœli wszystko siê wykona³o
**/
int checkFile1(string &file1Path, int &numOfStudent){
	
	ifstream file1;
	file1.open(file1Path.c_str());
	if(file1.fail()){
		cerr << "Nieudane otwarcie pliku " << file1Path << endl;
		file1.close();
		return 1;
	}
	string line;
	getline(file1, line);
	getline(file1, line);
	while(getline(file1, line)){
		numOfStudent++;
	}
	file1.close();
	return 0;	
}

/**
* Funkcja sortuj¹ca nazwy przedmiotów.
*
* @param przedmiotTxt wskaŸnik na tablice z nazwami przedmiotów
* @param ilPrzed wielkoœæ tablicy
**/
void bubbleSort(string *przedmiotTxt, const int ilPrzed){
	int i, j;
	string temp;
	for (i = 0; i<ilPrzed-1; i++){
		for (j=0; j<ilPrzed-1-i; j++){
			if (przedmiotTxt[j][0] > przedmiotTxt[j+1][0]){
				temp = przedmiotTxt[j+1];
				przedmiotTxt[j+1] = przedmiotTxt[j];
				przedmiotTxt[j] = temp;
			}
		}
    }
}

/**
* Funkcja sprawdza instnienie pliku i zawartoœæ pierszej linii.
*
* @param file2Path œcie¿ka do pliku, w którym bedziemy zapisywaæ
* @param stuTab wskaŸnik na tablice
* @param blad kod b³êdu
* @param num licznik do odlicznia studentów
* @param przedmiotTxt tablica z nazwami przedmiotów
* @param ilPrzed wielkoœæ tablicy przedmiotTxt
* @return zwraca kod b³êdu, 101 jeœli plik nie ma zapisanego imienia i nazwiska,
* 102 jeœli plik posiada zapisane imie i nazwisko, 103 jeœli plik nie istnieje, 1012 jeœli plik ma ju¿ dane, które chcemy wpisaæ
**/
int checkFile2(string &file2Path, Student *stuTab, Przedmiot &prz, int &blad, int &num){
	
	ifstream file2;
	file2.open(file2Path.c_str());
	if(file2.good()){

		string line;
		getline(file2, line);
		if(line.find(stuTab[num].imie + " " + stuTab[num].nazwisko, 0) == string::npos){
			while(getline(file2, line)){
					if(line.find(prz.prowadzacy + " " + prz.nazwa + " " + stuTab[num].ocena + " " + stuTab[num].dataWpisu, 0) == string::npos){
						blad = 101;
					}else{
							
					}
			}
			
			return blad;		// Plik nie posiada imienia i nazwiska
		}else{
			while(getline(file2, line)){
					if(line.find(prz.prowadzacy + " " + prz.nazwa + " " + stuTab[num].ocena + " " + stuTab[num].dataWpisu, 0) == string::npos){
						blad = 102;
					}else{
						blad = 1012;
						return blad;
					}				
			}
			
			return blad; 	// Plik posiada imie i nazwisko
		}
	}else{
		blad = 103;
		return blad; 	// Plik nie istnieje
	}
	file2.close();
}

/**
* Funkcja zapisuje dane do pliku ka¿dego studenta.
*
* @param stuTab wskaŸnik na tablice z której pochodz¹ dane do zapisu
* @param prz tablica z której pochodz¹ dane do zapisu
* @param przedmiotTxt tablica z nazwami przedmiotów
* @param ilPrzed wielkoœæ tablicy przedmiotTxt
* @param numOfStudent licznik wskazuj¹cy studenta
**/
void saveFile2(Student *stuTab, Przedmiot &prz, const int numOfStudent){
	for(int j = 0; j<numOfStudent; j++){		
		int blad = 0;
		
		string file2Path = "E:\\Prace\\c++\\Dziekanat\\OcenyStudenta\\" + stuTab[j].nrAlbumu + ".txt";
		fstream file2;
			
		checkFile2(file2Path, stuTab, prz, blad, j);
		if(blad == 101){
			file2.open(file2Path.c_str(), ios_base::out);
			file2 << stuTab[j].imie << " " << stuTab[j].nazwisko << endl << "nr albumu: " << stuTab[j].nrAlbumu << endl;
			file2 << prz.prowadzacy << " " << prz.nazwa << " " << stuTab[j].ocena << " " << stuTab[j].dataWpisu << endl;
		}else if(blad == 102){
			file2.open(file2Path.c_str(), ios_base::out | ios_base::app);
			file2 << prz.prowadzacy << " " << prz.nazwa << " " << stuTab[j].ocena << " " << stuTab[j].dataWpisu << endl;
		}else if(blad == 103){
			file2.open(file2Path.c_str(), ios_base::out);
			file2 << stuTab[j].imie << " " << stuTab[j].nazwisko << endl << "nr albumu: " << stuTab[j].nrAlbumu << endl;
			file2 << prz.prowadzacy << " " << prz.nazwa << " " << stuTab[j].ocena << " " << stuTab[j].dataWpisu << endl;
		}else{
			
		}
		file2.close();
	}
}

int main(int argc, char** argv) {
	
	setlocale(LC_CTYPE, "Polish");	// Polskie znaki w œrodku kodu
	//system("chcp 65001");	// Polskie znaki z zewn¹trz
	
	Student stu;
	Przedmiot prz;
	
	// Tablica z nazwami plików txt wpisanych przy uruchamianiu programu
	int ilPrzed = 0;
	string przedmiotTxt[ilPrzed] = {};
	
	// Sprawdzanie argumentów wejscia
	if(argc >= 3){
		int ilPrzed = argc-2;
		if(!string(argv[1]).compare("-i")){
			for(int i = 0; i<argc-2; i++){
				przedmiotTxt[i] = argv[i+2];
				
			}
		}else{
		cerr << "B³êdne argumenty wejsciowe!" << argv[1] << endl;
		return 1;
	}
	}else{
		cerr << "Zbyt ma³o argumentów!" << endl << "Aby poprawnie uruchomiæ program wpisz: " << endl;
		cerr << "nazwa_programu.exe -i nazwa_pliku.txt" << endl;
		cerr << "Mo¿esz podaæ dowoln¹ iloœæ istniej¹cych plików wejœciowych." << endl;
		return 1;
	}
	
	bubbleSort(przedmiotTxt, ilPrzed);
	
	cout << "Odczytano dane z pliku: ";
	
	for(int i = 0; i<ilPrzed; ++i){
		
		int numOfStudent = 0;
		string file1Path = przedmiotTxt[i];
		cout << file1Path << " | ";
		if(checkFile1(file1Path, numOfStudent)){
			return 2;
		}
		
		ifstream file1;
		file1.open(file1Path.c_str());
		
		Student *stuTab = new Student[numOfStudent];
		
		readPrzedmiot(file1, prz);
		readStuTab(file1, stuTab, numOfStudent);
		file1.close();
		saveFile2(stuTab, prz, numOfStudent);

		delete[] stuTab;
	}
	cout << endl;
	system("pause");
	return 0;
}


