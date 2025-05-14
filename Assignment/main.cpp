#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <array>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <ranges>

using namespace std;

class Player {
public:
	Player() :id{}, score{}, num{} {}
	Player(const Player& other)  
		: name{other.name}, score{other.score}, id{other.id}, num{other.num}
	{
		p = std::make_unique<char[]>(num);
		memcpy(p.get(), other.p.get(), num);
	}
	Player& operator=(const Player& other) {
		if (this == &other)
			return *this;
		name = other.name;
		score = other.score;
		id = other.id;
		num = other.num;

		p.release();
		p = std::make_unique<char[]>(num);
		memcpy(p.get(), other.p.get(), num);

		return *this;
	}

	bool operator<(const Player& rhs) const {
		return id < rhs.id;
	}

	void sort() {
		std::sort(p.get(), p.get() + num);
	}

	// 'a'�� ���� ����
	size_t CountA() {
		int cnt{};
		for (int i = 0; i < num; ++i) {
			if ('a' == p[i]) {
				++cnt;
			}
			else {
				// �̹� ���ĵǾ��ֱ� ������ �ߴ�
				break;
			}
		}
		return cnt;
	}

	int GetScore() const { return score; }
	size_t GetID() const { return id; }
	string GetName() const { return name; }

	void write(ostream& os) {
		os.write((char*)this, sizeof(Player));
		os.write((char*)p.get(), num);
	}
	void read(istream& is) {
		is.read((char*)this, sizeof(Player));
		p.release();
		p = make_unique<char[]>(num);
		is.read((char*)p.get(), num);
	}

	friend ostream& operator<<(ostream& os, const Player& other) {
		os << "�̸�: " << other.name << ", ���̵�: " << other.id << ", ����: " << other.score
			<< ", �ڿ���: " << other.num << endl;
		os << "����� ����: ";
		for (int i = 0; i < other.num; ++i) {
			os << other.p[i];
		}
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
	ifstream in{ "2025 STL ���� ���� - 2022180039", ios::binary };
	if (not in) {
		throw 2022180039;
	}

	// 1
	for (int i = 0; i < players.size(); ++i) {
		players[i].read(in);
	}
	cout << "������ player�� ����" << endl;
	cout << players.back() << endl;

	// 2
	cout << "���� ū ������ ���� player\n" << *max_element(players.begin(), players.end()) << endl;
	//sort(players.begin(), players.end());
	//cout << players.back() << endl;

	double average = (double)accumulate(players.begin(), players.end(), 0, [](size_t sum, const Player& p) {
		return sum + p.GetScore();
		}) / players.size();
	cout << "score ��� ��: " << average << endl;
	cout << endl;

	// 3
	unordered_map<size_t, vector<Player>> equal_id;
	for (const Player& player : players) {
		equal_id[player.GetID()].push_back(player);
	}

	// �ϳ��� ����
	for (auto it = equal_id.begin(); it != equal_id.end(); ) {
		if (it->second.size() == 1)
			it = equal_id.erase(it);
		else
			++it;
	}

	// ���� ���
	/*ofstream out{ "�������̵�.txt" };
	for (const auto& [id, player] : equal_id) {
		for (const Player p : player) {
			out << "�̸�: " << p.GetName() << endl;
			out << "���̵�: " << p.GetID() << endl;
		}
	}*/
	cout << "���� ���̵� ���� ��ü�� ����: " << equal_id.size() << endl;
	cout << endl;

	// 4
	for (Player& player : players) {
		player.sort();
	}

	int cnt{};
	for (Player& player : players) {
		if (10 <= player.CountA()) {
			++cnt;
		}
	}

	cout << "'a'�� 10���� �̻��� ��ü�� ����: " << cnt << endl;
	cout << endl;
}