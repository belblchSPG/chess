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

	//������������� ������ ��� ����� (����� ������������� ��� ��������, ���� ������ ������ ���� ������. ����� ��� ������������� � ������ ����� ���������� ������ ������� �����������))
	Figure(figureTypes figType) : figureType{ figType } {};
};



//���������, ����������� ������ �� �����
struct Cell {

	Color color;
	Figure figureOnCell{empty};//������ ������ ���������������� ��� ������ �� ���
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


//���������, ����������� ��������� �����
struct Chessboard {

	Cell cells[8][8]; //������ ������ - �����, ������ ������ - �����
};

//�������, ������� ��������� ����� �� �� ����� ������. ����� ���, �������������� ����� ��� ����� ������ ��������, ����� �������, ��������������� ��������� �����.
bool isCellEmpty(const Chessboard chessboard, letterCoordinates letterCoordinate, numericCoordinates numericCoordinate) {

		if (chessboard.cells[numericCoordinate][letterCoordinate].figureOnCell.figureType == 'E') {

			return true;
		}
	return false;
}

//�������, ������� ��������� ����� �� �� ����� ������. ����� ���, �������������� ������ ��� ���������� ��������� �����. � ������ ������� �������������� ��������, ������� ����������� ����.
bool isCellEmpty(const Chessboard chessboard, char letterCoordinate, int numericCoordinate) {

	if (chessboard.cells[numericCoordinate][letterCoordinate - 65].figureOnCell.figureType == 'E') {

		return true;
	}
	return false;
}

//�������, ������� ���� ���� ������� �� ��������� ����� ����� (������ � �����).
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

//�������, ������� ������������� ��������� ����� � �������.
void printBoard(const Chessboard chessboard) {

	for (int i = 0; i < 8; i++) {
		//���������� ���� �� ��������� �����.
		cout << 8 - i << "|";
		for (int j = 0; j < 8; j++) {

			//���� �� ������ ��� ������, ��������������� ���� ������.
			if (isCellEmpty(chessboard, char(65 + j), i)) {

				if (chessboard.cells[i][j].color == white) {
					cout << "_|";
				}
				if (chessboard.cells[i][j].color == black) {
					cout << "*|";
				}
			}
			else {
				switch (chessboard.cells[i][j].figureOnCell.figureType) //���� �� ������ ����� ������ ������, �� ��� ������������� �� ����� � �������.
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
	//���������� ���� �� ��������� �����
	for (int i = 0; i < 8; i++) {
		if (i == 0) { cout << ' '; }
		cout << "|" << char(65+i);
		if (i == 7) { cout << '|'; }
	}
}

//�������, ������� ������ ������ ��� ����������� �� ������������ �����, �.�. ������ ������ ������ �� ��������� �����, ���� �� ��� �� ������ �� ���� ������.
Chessboard placeFigure(Chessboard& chessboard,Figure figure, letterCoordinates letterCoordinate, numericCoordinates numericCoordinate) {

	//�������� �� ��, ����� �� �� ������ ������, ���� �� �����, �� �� ������ �������� ������.
	if (isCellEmpty(chessboard, letterCoordinate, numericCoordinate)) {
		chessboard.cells[numericCoordinate][letterCoordinate].figureOnCell.figureType = figure.figureType; 
		return chessboard;
	}
}

//����������� ������� �� ����� ������, �� �������� ��������.
void checkFigures(const Chessboard chessboard) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {

			cout << chessboard.cells[i][j].figureOnCell.figureType << ' ';
		}
		cout << endl;
	}
}

//������� ��������� ���� �� �� ����������� ��������� ����� ������ (� �������, ���� � ���� ��������� ���� �� ������ �� ����� A5-H5, A1-H1 � �.�.)
//���� �� ����������� ��� �����, �� ������� ���������� true (����� �������), ���� ���� ������ �� false (������� ������).
bool checkHorizontallyEmpty(const Chessboard chessboard, letterCoordinates lettCoordinate, numericCoordinates numCoordinate) {

	for (int i = 0; i < 8; i++) {
		if (!isCellEmpty(chessboard, letterCoordinates(i), numericCoordinates(numCoordinate))) {
			return false;
		}
	}
	return true;
}

//����������� �������� �� ����������� �������� �� ���������.
bool checkVerticallyEmpty(const Chessboard chessboard, letterCoordinates lettCoordinate, numericCoordinates numCoordinate) {

	for (int i = 0; i < 8; i++) {
		if(!isCellEmpty(chessboard, letterCoordinates(lettCoordinate), numericCoordinates(i))) {
			return false;
		}
	}
	return true;
}

//����������� �������� �� ����������� � ��������� �������� �� ��������� �� ���������.
bool checkDiagonallyEmpty(const Chessboard chessboard, letterCoordinates lettCoordinate, numericCoordinates numCoordinate) {

	int j = lettCoordinate;
	int i = numCoordinate;

	//������ ����� ��� �������� ���� 4 ��������� ����������� �� ���������. �.� �����-������, ������-������, �����-����, ������-����.
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

//������ �������� ������� �� ���� ������������, �.� �������� �� �����������, ��������� � ���������.
bool checkPosition(const Chessboard chessboard, letterCoordinates lettCoordinate, numericCoordinates numCoordinate) {

	if (checkHorizontallyEmpty(chessboard, lettCoordinate, numCoordinate) && checkVerticallyEmpty(chessboard, lettCoordinate, numCoordinate) && checkDiagonallyEmpty(chessboard, lettCoordinate, numCoordinate)) {
		return true;//���� ����� ���������, �� ������� ���������� true.
	}
	return false;//���� �� ���������, �� ������� ���������� false.
}

//������� ����������� ������� placeFigure, �� ������ ������� ����� ���������� ������ ��������� ������������ �����, � ������� �������� ������.
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