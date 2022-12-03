#include <iostream>
#include <vector>

using std::cout;
using std::endl;

enum Color : char{

	white = 'w',
	black = 'b'
};

enum figureTypes : char {

	king = 'K',
	queen = 'Q',
	bishop = 'B',
	horse = 'H',
	pawn = 'P',
	empty = 'E'
};

struct Figure {

	Color color;
	figureTypes figureType;

	//Инициализация фигуры без цвета (может потребоваться при ситуации, если каждая фигура бьет каждую. Тогда при инициализации к фигуре будут относиться только правила перемещения))
	Figure(figureTypes figType) : figureType{ figType } {};
};



//Структура, описывающая клетку на доске
struct Cell {

	Color color;
	Figure figureOnCell{empty};//Каждая клетка инициализируется без фигуры на ней
};

enum letterCoordinates : int {

	_A = 0,
	_B = 1,
	_C = 2,
	_D = 3,
	_E = 4,
	_F = 5,
	_G = 6,
	_H = 7
};

enum numericCoordinates : int {

	_8 = 0,
	_7 = 1,
	_6 = 2,
	_5 = 3,
	_4 = 4,
	_3 = 5,
	_2 = 6,
	_1 = 7
};

struct Coordinate
{
	letterCoordinates lettCoord;
	numericCoordinates numCoord;
};


//Структура, описывающая шахматную доску
struct Chessboard {

	Cell cells[8][8]; //Первый размер - цифра, второй размер - буква
};

//Функция, которая првоеряет стоит ли на доске фигура. Вроде как, использовалась везде где нужна данная проверка, кроме функции, распечатывающей шахматную доску.
bool isCellEmpty(const Chessboard chessboard, letterCoordinates letterCoordinate, numericCoordinates numericCoordinate) {

		if (chessboard.cells[numericCoordinate][letterCoordinate].figureOnCell.figureType == 'E') {

			return true;
		}
	return false;
}

//Функция, которая проверяет стоит ли на доске фигура. Вроде как, использовалась только при распечатке шахматной доски. В других случаях использовалась функиция, которая расположена выше.
bool isCellEmpty(const Chessboard chessboard, char letterCoordinate, int numericCoordinate) {

	if (chessboard.cells[numericCoordinate][letterCoordinate - 65].figureOnCell.figureType == 'E') {

		return true;
	}
	return false;
}

//Функция, которая дает всем клеткам на шахматной доске цвета (черный и белый).
Chessboard paintBoard(Chessboard& chessboard) {

	int col = 1;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (col == 1) {

				chessboard.cells[i][j].color = white;
				col = -1;
			}
			else if (col == -1) {
				chessboard.cells[i][j].color = black;
				col = 1;
			}
		}
		col = -col;
	}
	return chessboard;
}

//Функция, которая распечатывает шахматную доску в консоль.
void printBoard(const Chessboard chessboard) {

	for (int i = 0; i < 8; i++) {
		//Распечатка цифр на шахматной доске.
		cout << 8 - i << "|";
		for (int j = 0; j < 8; j++) {

			//Если на клетке нет фигуры, распечатывается цвет клетки.
			if (isCellEmpty(chessboard, char(65 + j), i)) {

				if (chessboard.cells[i][j].color == white) {
					cout << "_|";
				}
				if (chessboard.cells[i][j].color == black) {
					cout << "*|";
				}
			}
			else {
				switch (chessboard.cells[i][j].figureOnCell.figureType) //Если на клетке будет стоять фигура, то она распечатается на доске в консоле.
				{
				case king: {cout << "K|"; continue; }
				case queen: {cout << "Q|"; continue; }
				case bishop: {cout << "B|"; continue; }
				case horse: {cout << "H|"; continue; }
				case pawn: {cout << "P|"; continue; }

				default:
					break;
				}
			}
		}
		cout << endl;
	}
	//Распечатка букв на шахматной доске
	for (int i = 0; i < 8; i++) {
		if (i == 0) { cout << ' '; }
		cout << "|" << char(65+i);
		if (i == 7) { cout << '|'; }
	}
}

//Функция, которая ставит фигуру вне зависимости от безопасности место, т.е. просто ставит фигуру на выбранное место, если до нее на клетке не было фигуры.
Chessboard placeFigure(Chessboard& chessboard,Figure figure, letterCoordinates letterCoordinate, numericCoordinates numericCoordinate) {

	//Проверка на то, стоит ли на клетке фигура, если не стоит, то на клетку ставится фигура.
	if (isCellEmpty(chessboard, letterCoordinate, numericCoordinate)) {
		chessboard.cells[numericCoordinate][letterCoordinate].figureOnCell.figureType = figure.figureType; 
		return chessboard;
	}
}

//Использовал функцию во время тестов, не обращать внимания.
void checkFigures(const Chessboard chessboard) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {

			cout << chessboard.cells[i][j].figureOnCell.figureType << ' ';
		}
		cout << endl;
	}
}

//Функция проверяет есть ли на горизонтали шахматной доски фигуры (к примеру, если я хочу проверить есть ли фигуры на линии A5-H5, A1-H1 и т.д.)
//Если на горизонтали нет фигур, то функция возвращает true (можно ставить), если есть фигура то false (ставить нельзя).
bool checkHorizontallyEmpty(const Chessboard chessboard, letterCoordinates lettCoordinate, numericCoordinates numCoordinate) {

	for (int i = 0; i < 8; i++) {
		if (!isCellEmpty(chessboard, letterCoordinates(i), numericCoordinates(numCoordinate))) {
			return false;
		}
	}
	return true;
}

//Аналогичная проверке по горизонтали проверка по вертикали.
bool checkVerticallyEmpty(const Chessboard chessboard, letterCoordinates lettCoordinate, numericCoordinates numCoordinate) {

	for (int i = 0; i < 8; i++) {
		if(!isCellEmpty(chessboard, letterCoordinates(lettCoordinate), numericCoordinates(i))) {
			return false;
		}
	}
	return true;
}

//Аналогичная проверке по горизонтали и вертикали проверка по вертикали по диагонали.
bool checkDiagonallyEmpty(const Chessboard chessboard, letterCoordinates lettCoordinate, numericCoordinates numCoordinate) {

	int j = lettCoordinate;
	int i = numCoordinate;

	//Четыре цикла для проверки всех 4 возможных направлений по диагонали. Т.е влево-наверх, вправо-наверх, влево-вниз, вправо-вниз.
	while (i > -1 && i < 8 && j > -1 && j < 8) {

		if (!isCellEmpty(chessboard, letterCoordinates(j), numericCoordinates(i))) {
			return false;
		}
		j--;
		i--;
	}

	j = lettCoordinate;
	i = numCoordinate;
	while (i > -1 && i < 8 && j > -1 && j < 8) {

		if (!isCellEmpty(chessboard, letterCoordinates(j), numericCoordinates(i))) {
			return false;
		}
		j--;
		i++;
	}

	j = lettCoordinate;
	i = numCoordinate;
	while (i > -1 && i < 8 && j > -1 && j < 8) {

		if (!isCellEmpty(chessboard, letterCoordinates(j), numericCoordinates(i))) {
			return false;
		}
		j++;
		i--;
	}

	j = lettCoordinate;
	i = numCoordinate;
	while (i > -1 && i < 8 && j > -1 && j < 8) {

		if (!isCellEmpty(chessboard, letterCoordinates(j), numericCoordinates(i))) {
			return false;
		}
		j++;
		i++;
	}

	return true;
}

//Полная проверка позиции по всем направлениям, т.е проверка по горизонтали, вертикали и диагонали.
bool checkPosition(const Chessboard chessboard, letterCoordinates lettCoordinate, numericCoordinates numCoordinate) {

	if (checkHorizontallyEmpty(chessboard, lettCoordinate, numCoordinate) && checkVerticallyEmpty(chessboard, lettCoordinate, numCoordinate) && checkDiagonallyEmpty(chessboard, lettCoordinate, numCoordinate)) {
		return true;//Если место безопасно, то функция возвращает true.
	}
	return false;//Если не безопасно, то функция возвращает false.
}

//Функция аналогичная функции placeFigure, но данная функция перед установкой фигуры проверяет безопасность места, в которое ставится фигура.
Chessboard placeFigureSafe(Chessboard& chessboard,Figure figure, letterCoordinates lettCoordinate, numericCoordinates numCoordinate) {

	if (checkPosition(chessboard, lettCoordinate, numCoordinate)) {
		return placeFigure(chessboard, figure, lettCoordinate, numCoordinate);
	}

	return chessboard;
}



Chessboard setQueens(Chessboard& chessboard, int numberOfQueens, letterCoordinates lettFirstFigureCoordinate, numericCoordinates numFirstFigureCoordinate) {
	placeFigureSafe(chessboard, queen, lettFirstFigureCoordinate, numFirstFigureCoordinate);

	int figureCount = 0; 
	while(figureCount != numberOfQueens){
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
	
				placeFigureSafe(chessboard, queen, letterCoordinates(j), numericCoordinates(i));
				if (isCellEmpty(chessboard, letterCoordinates(j), numericCoordinates(i))) {
					figureCount++;
				}
			}
		}
	}
	return chessboard;
}


int main() {

	Chessboard a;
	paintBoard(a);
	setQueens(a, 3, _B, _8);
	printBoard(a);


	return 1;
}