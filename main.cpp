#include <vector>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

using namespace std;

struct score
{
	int s1, s2, stotal;
};
class player
{
public:
	score scores[12];
	string name;
	player(int x, string myname);
	player();
	void displayScore(int frame);
	void newScore(int frame, score newscore);
};
void endfunction(player players[], int numplay);
int validate(int score);
string validateName(string name);
int main()
{
	system("title BOWLING");
	int numplay;
inputplayers:
	cout << "Enter number of players:" << endl << ">";
	cin >> numplay;
	if (numplay < 0 || numplay > 6)
		goto inputplayers;
	player players[6];
	string name;
	for (int x = 0; x < numplay; x++)
	{
		cout << "Enter name for player " << x + 1 << ": ";
		cin >> name;
		name = validateName(name);
		players[x] = player(x, name);
	}
	system("cls");
	for (int currentFrame = 0; currentFrame < 9; currentFrame++)
	{
		for (int currentPlayer = 0; currentPlayer < numplay; currentPlayer++)
		{
		inputscores:
			cout << " ___________________________________________________________________________" << endl
				<< "|Name    |     |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10  |" << endl;
			players[currentPlayer].displayScore(currentFrame);
			int score1 = 0, score2 = 0, scoretotal = 0;
			cout << "Enter data for player: " << players[currentPlayer].name << endl
				<< "Frame: " << currentFrame + 1 << endl
				<< "Pins hit with first roll: ";
			cin >> score1;
			score1 = validate(score1);
			if (score1 < 10)
			{
				cout << "Pins hit with second roll: ";
				cin >> score2;
				score2 = validate(score2);
			}
			else {
				cout << endl << "STRIKE!" << endl << endl;
			}
			if (score1 + score2 > 10 || score1 + score2 < 0)
			{
				cout << "These scores do not match. Please enter alternate scores." << endl;
				system("pause");
				system("cls");
				goto inputscores;
			}
			else
			{
				scoretotal = score1 + score2;
			}
			if (scoretotal == 10 && score1 != 10)
			{
				cout << endl << "SPARE!" << endl << endl;
			}
			score newframe;
			newframe.s1 = score1;
			newframe.s2 = score2;
			newframe.stotal = scoretotal;
			players[currentPlayer].newScore(currentFrame, newframe);
			system("pause");
			system("cls");
		}
	}
	for (int currentPlayer = 0; currentPlayer < numplay; currentPlayer++)
	{
	inputlastscore:
		cout << " ___________________________________________________________________________" << endl
			<< "|Name    |     |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10  |" << endl;
		players[currentPlayer].displayScore(9);
		int score1 = 0, score2 = 0, score3 = 0, scoretotal = 0;
		bool third = false;
		cout << "Enter data for player: " << players[currentPlayer].name << endl
			<< "LAST FRAME!" << endl
			<< "Pins hit with first roll: ";
		cin >> score1;
		score1 = validate(score1);
		if (score1 < 10)
		{
			cout << "Pins hit with second roll: ";
			cin >> score2;
			score2 = validate(score2);
		}
		else {
			cout << endl << "STRIKE!" << endl;
			cout << "Enter next roll: ";
			cin >> score2;
			score2 = validate(score2);
			if (score2 == 10)
			{
				cout << "Great!" << endl;
			}
			third = true;
			cout << "Enter your LAST ball: ";
			cin >> score3;
			score3 = validate(score3);
			if (score3 == 10)
			{
				cout << "AMAZING!" << endl;
			}
		}
		if ((score1 + score2 > 10 && score1 != 10))
		{
			cout << "These scores do not match. Please enter alternate scores." << endl;
			system("pause");
			system("cls");
			goto inputlastscore;
		}
		else
		{
			score newframe;
			newframe.s1 = score1;
			newframe.s2 = 0;
			newframe.stotal = score1;
			players[currentPlayer].newScore(9, newframe);
			newframe.s1 = score2;
			newframe.stotal = score2;
			players[currentPlayer].newScore(10, newframe);
		}
		if (score1 + score2 == 10 && score1 != 10)
		{
			cout << endl << "SPARE!" << endl << endl;
			cout << "Nice!" << endl;
			cout << "Enter your LAST ball: ";
			cin >> score3;
			validate(score3);
			if (score3 == 10)
			{
				cout << "AMAZING!" << endl;
			}
			third = true;
		}
		if (third)
		{
			score newframe;
			newframe.s1 = score3;
			newframe.s2 = 0;
			newframe.stotal = score3;
			players[currentPlayer].newScore(11, newframe);
		}
		else {
			score newframe;
			newframe.s1 = -1;
			newframe.s2 = 0;
			newframe.stotal = 0;
			players[currentPlayer].newScore(11, newframe);
		}
		system("pause");
		system("cls");
	}
	endfunction(players, numplay);
	return 0;
}
string validateName(string name)
{
	while (name.length() > 7)
	{
		string dummy;
		getline(cin, dummy);
		cout << endl << "Your name is too long." << endl;
		cout << "Enter nickname: ";
		cin >> name;
	}
	return name;
}
player::player(int x, string myname)
{
	name = myname;
}
player::player()
{
}
void player::newScore(int frame, score newscore)
{
	scores[frame] = newscore;
	if (frame > 0 && frame < 9)
	{
		if (scores[frame - 1].s1 + scores[frame - 1].s2 == 10)
		{
			scores[frame - 1].stotal += scores[frame].s1;
		}
		if (scores[frame - 1].s1 == 10 && scores[frame].s1 != 10)
		{
			scores[frame - 1].stotal += scores[frame].s2;
		}
	}
	if (frame > 1 && frame < 9)
	{
		if (scores[frame - 2].s1 == 10 && scores[frame - 1].s1 == 10)
		{
			scores[frame - 2].stotal += scores[frame].s1;
			scores[frame - 1].stotal += scores[frame].s1;
		}
	}
	if (frame == 9) {
		if (scores[frame - 1].s1 + scores[frame - 1].s2 == 10)
		{
			scores[frame - 1].stotal += scores[frame].s1;
		}
		if (scores[frame - 1].s1 == 10 && scores[frame].s1 != 10)
		{
			scores[frame - 1].stotal += scores[frame].s2;
		}
		if (scores[frame - 2].s1 == 10 && scores[frame - 1].s1 == 10)
		{
			scores[frame - 2].stotal += scores[frame].s1;
			scores[frame - 1].stotal += scores[frame].s1;
		}
	}
	if (frame == 10)
	{
		if (scores[frame - 2].s1 == 10)
		{
			scores[frame - 2].stotal += scores[frame].s1;
		}
	}
	if (frame == 11)
	{
		if (scores[11].s1 > -1)
			scores[11].stotal = scores[8].stotal + scores[9].s1 + scores[10].s1 + scores[11].s1;
		else
			scores[11].stotal = scores[8].stotal + scores[9].s1 + scores[10].s1;
	}
	if (frame > 0 && frame !=11)
	{
		scores[frame].stotal += scores[frame - 1].stotal;
	}
}
int validate(int myscore)
{
	if (myscore >= 0 && myscore <= 10)
		return myscore;
	else
	{
		cout << endl << "Error, invalid score. Enter alternate score: ";
		cin >> myscore;
		validate(myscore);
	}
}
void player::displayScore(int frame)
{
	cout << "|--------|------------------------------------------------------------------|" << endl
		<< "|        |Score|";
	for (int i = 0; i < 9; i++)
	{
		if (i < frame)
		{
			cout << setw(2);
			if (scores[i].s1 == 10)
			{
				cout << 'X';
			}
			else
			{
				cout << scores[i].s1;
			}
			cout << "|";
			if (scores[i].s1 == 10)
				cout << "  |";
			else
			{
				cout << setw(2);
				if (scores[i].s2 + scores[i].s1 == 10 && scores[i].s1 != 10)
					cout << '/' << "|";
				else
					cout << scores[i].s2 << "|";
			}
		}
		else
		{
			cout << "  |  |";
		}
	}
	if (10 < frame)
	{
		if (scores[9].s1 == 10)
			cout << "X" << "|";
		else
			cout << scores[9].s1 << "|";
		if (scores[10].s1 + scores[9].s1 == 10 && scores[9].s1 != 10)
			cout << "/" << "|";
		else if (scores[9].s1 != 10)
			cout << scores[10].s1 << "|";
		else
			cout << "X" << "|";
		if (scores[11].s1 == 10)
			cout << " X" << "|";
		else if (scores[11].s1 > -1)
			cout << " " << scores[11].s1 << "|";
		else
			cout << "  |";
	}
	else {
		cout << " | |  |";
	}
	cout << endl << "|        |";
	for (int i = 0; i < 66; i++)
		cout << "-";
	cout << "|" << endl << "| " << setw(7) << name << "|     |     |     |     |     |     |     |     |     |     |      |" << endl << "|        |Total|";
	for (int i = 0; i < 9; i++)
	{
		if (i < frame)
			cout << setw(4) << scores[i].stotal << " |";
		else
			cout << "     |";
	}
	if (10 < frame)
		cout << setw(4) << scores[11].stotal << "  |";
	else
		cout << "      |";
	cout << endl;
	cout << "|________|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|______|" << endl << endl;
}
void endfunction(player players[], int numplay)
{
	///Display full scoreboard with all players
	cout << " ___________________________________________________________________________" << endl
		<< "|Name    |     |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10  |" << endl;
	for (int x = 0; x < numplay; x++)
		players[x].displayScore(1000);
}
