#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <array>

using namespace std;

class Player {
public:
	void write(ostream& os) {
		os.write((char*)this, sizeof(Player));
		os.write((char*)p.get(), num);
	}
	void read(istream& is) {
		/*1�� ��ü �̸� : tbgkdyf, ���̵� : 1585002, ���� : 225936740, �ڿ��� : 482
		2�� ��ü �̸� : ebodemiipwcovky, ���̵� : 960538, ���� : 353919937, �ڿ��� : 231
		3�� ��ü �̸� : bupee, ���̵� : 250535, ���� : 275456330, �ڿ��� : 16
		4�� ��ü �̸� : bwdgnvrstnxo, ���̵� : 2221181, ���� : 22271892, �ڿ��� : 269
		5�� ��ü �̸� : hnln, ���̵� : 550535, ���� : 276748627, �ڿ��� : 245
		6�� ��ü �̸� : dvrlgaiqnnmtqe, ���̵� : 2296425, ���� : 226278669, �ڿ��� : 426
		7�� ��ü �̸� : rnfsutjmxth, ���̵� : 1699554, ���� : 205153856, �ڿ��� : 32
		8�� ��ü �̸� : hqqkntxtbcuxu, ���̵� : 1956483, ���� : 278670016, �ڿ��� : 282
		9�� ��ü �̸� : vcoyimkqeyohal, ���̵� : 2012612, ���� : 380493315, �ڿ��� : 358*/

		is.read((char*)this, sizeof(Player));
		p = make_unique<char[]>(num);
		is.read((char*)p.get(), num);
	}

	friend ostream& operator<<(ostream& os, const Player& other) {
		os << "�̸�: " << other.name << ", ���̵�: " << other.id << ", ����: " << other.score
			<< ", �ڿ���: " << other.num << endl;
		os << "����� ����: ";
		/*for (int i = 0; i < other.num; ++i) {
			os << other.p[i];
		}*/
		os << endl;
		return os;
	}
private:
	string name; // �̸�, ����[3, 15],  ['a', 'z']�θ� ����
	int score; // ����
	size_t id; // ���̵�, ��ġ�� ���̵� ���� �� ����
	size_t num; // free store�� Ȯ���� ����Ʈ ��
	unique_ptr<char[]> p; // free store�� Ȯ���� �޸�
};


array<Player, 2'500'000> players;

int main()
{
	ifstream in{ "2025 STL ���� ���� - 2022180039", ios::binary};
	if (not in) {
		throw 2022180039;
	}

	for (int i = 0; i < players.size(); ++i) {
		players[i].read(in);
	}

	for (const Player& player : players) {
		cout << player << endl;
	}
}