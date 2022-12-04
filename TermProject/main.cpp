#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <sstream>

using namespace std;
std::vector<string> vec;
string str;
string notice;
string temp_str;
//벡터에 해당 str단어 단위로 출력

//인풋 팩토리메서드

void addvector(string astr) {
	int add = 0;
	int i = 0;
	while ((astr.length() - i) >= 75) {
		string substr = astr.substr(i, 75);

		if (astr.substr(i + 75, 1).compare(" ") == 0) {
			add = 75;
			vec.push_back(substr);
			i += add;
		}
		else {
			std::vector<string> svec;
			istringstream s(substr);
			string sb;
			while (getline(s, sb, ' ')) {
				svec.push_back(sb);
			}
			if (astr.substr(i + 74, 1).compare(" ") != 0) {
				add = substr.length() - (svec.back().length());
				vec.push_back(astr.substr(i, add));
			}
			else
			{
				add = substr.length();
				vec.push_back(astr.substr(i, add));
			}

			i += add;
		}
	}
	vec.push_back(astr.substr(i, astr.length() - i));
};




int main(void) {
	std::ifstream readFile;
	std::ofstream writeFile;
	readFile.open("test.txt");
	std::getline(readFile, str);
	addvector(str);
	//vec에 각 라인 집어넣기

	bool p_lock = false;
	bool lock = true;

	int ln = 0;
	int crn_ln = 0;
	int p = 0;
	while (1) {
		int j = 1;
		for (int k = p; k < p + 20; k++) {
			cout.width(2);
			std::cout << std::right << j << "|" << vec.at(k) << std::endl;
			j++;
		}
		std::cout << "-------------------------------------------------------------------------------" << std::endl;
		std::cout << "n:다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장후정료" << std::endl;
		std::cout << "-------------------------------------------------------------------------------" << std::endl;
		std::cout << notice << std::endl;
		notice = "";
		std::cout << "-------------------------------------------------------------------------------" << std::endl;
		string input;
		std::cin >> input;
		std::cout << "-------------------------------------------------------------------------------" << std::endl;

		if (input.compare("t") == 0) {
			readFile.close();
			ofstream writeFile;
			writeFile.open("test.txt");
			for (auto element : vec) {
				writeFile.write(element.c_str(), element.size());
			}

			writeFile.close();
			break;
		}
		else if (input.substr(0, 1).compare("i") == 0) {

			string input_str = input.substr(2, input.length() - 3);
			istringstream ss(input_str);
			string stringBuffer;
			string index;
			vector<int> k;
			int count = 0;
			//vec k에 int값 집어넣기+집어넣는 문자열=index
			try {

				while (getline(ss, stringBuffer, ',')) {

					if (count == 2) {
						index = stringBuffer;
						break;
					}
					for (int i = 0; i < stringBuffer.length(); i++) {
						if (isdigit(stringBuffer[i]) == 0) {
							throw stringBuffer;
						}
					}

					//숫자의 값이 해당줄과 인덱스를 넘지않으면 예외처리
					if (count == 0 && (std::stoi(stringBuffer) > 0 && std::stoi(stringBuffer) <= 20)) {
						k.push_back(std::stoi(stringBuffer));
						count++;
					}
					else if (count == 1 && (std::stoi(stringBuffer) >= 0 && std::stoi(stringBuffer) < 75)) {
						k.push_back(std::stoi(stringBuffer));
						count++;
					}

					else {
						throw stringBuffer;
					}
				}
			}
			catch (string stringBuffer) {

				notice = "please retry";
				continue;
			}
			//예외
			if (k.front())
				//string x = vec.at(k.front() - 1);
				//vec.at(k.front() - 1) = x.substr(0, k.back()) + index + x.substr(k.back(), x.length() - k.back());

				for (int i = p; i < p + k.front() - 1; i++) {
					crn_ln += vec.at(i).length();
				}

			string old_str = str;
			str = old_str.substr(0, ln + crn_ln + k.back()) + index + old_str.substr(ln + crn_ln + k.back(), old_str.length() - k.back() - ln - crn_ln);

			k.clear();
			vec.clear();
			addvector(str);
			crn_ln = 0;
		}
		else if (input.substr(0, 1).compare("d") == 0) {

			string input_str = input.substr(2, input.length() - 3);
			istringstream ss(input_str);
			string stringBuffer;
			vector<int> k;
			int d_count = 0;
			try {
				while (getline(ss, stringBuffer, ',')) {
					for (int i = 0; i < stringBuffer.length(); i++) {
						if (isdigit(stringBuffer[i]) == 0) {
							throw stringBuffer;
						}
					}
					k.push_back(std::stoi(stringBuffer));
					if (d_count == 0 && (std::stoi(stringBuffer) > 0 && std::stoi(stringBuffer) <= 20)) {
						k.push_back(std::stoi(stringBuffer));
						d_count++;
					}
					else if (d_count == 1 && (std::stoi(stringBuffer) >= 0 && std::stoi(stringBuffer) < 75)) {
						k.push_back(std::stoi(stringBuffer));
						d_count++;
					}
					else if (d_count == 2) {
						k.push_back(std::stoi(stringBuffer));
					}
					else {
						throw stringBuffer;
					}
				}
			}
			catch (string stringBuffer) {
				notice = "please retry";
				continue;
			}
			for (int i = p; i < p + k.front() - 1; i++) {
				crn_ln += vec.at(i).length();
			}
			
			string old_str = str;
			int remain = crn_ln + k.at(1);


			str = old_str.substr(0, ln + remain - k.back()) + old_str.substr(ln + remain, old_str.length() - remain - ln);
			vec.clear();
			addvector(str);
			crn_ln = 0;
		}
		else if (input.substr(0, 1).compare("s") == 0) {
			bool ss = false;
			int vec_idx, word_idx;
			string input_str = input.substr(2, input.length() - 3);
			for (int i = 0; i < vec.size(); i++) {
				string vec_str = vec.at(i);
				if (vec_str.find(input_str) == string::npos) {
					continue;
				}
				else {
					ss = true;
					vec_idx = i;
					word_idx = vec_str.find(input_str);
					break;
				}

			}
			//찾지 못하면 다시 요구하도록 예외처리
			if (ss == false) {
				notice = "there isnt " + input_str;
				continue;
			}

			ln = 0;
			for (int i = 0; i < vec_idx; i++) {
				ln += vec.at(i).length();
			}
			ln += word_idx;
			vec.clear();
			string	first_str = str.substr(0, ln);

			for (int i = first_str.length(); i >= 0; i = i - 75) {
				string fsv;
				if (i < 75) {
					fsv = first_str.substr(0, i);
					vec.insert(vec.begin(), fsv);
					break;
				}
				//줄 처음이 띄어져있을 때
				if (first_str.substr(i - 75, 1).compare(" ") == 0) {
					fsv = first_str.substr(i - 75, 75);
				}
				//줄 처음이 글로 시작한다
				//그 중에서도 단어가 바로 시작할 때
				else {
					if (first_str.substr(i - 76, 1).compare(" ") == 0 && first_str.substr(i - 75, 1).compare(" ") != 0) {
						fsv = first_str.substr(i - 75, 75);
					}
					else if (first_str.substr(i - 76, 1).compare(" ") != 0 && first_str.substr(i - 75, 1).compare(" ") != 0) {
						string fs_slice = first_str.substr(i - 75, 75);
						int f_idx = fs_slice.find(" ");
						fsv = first_str.substr(i - 75 + f_idx, 75 - f_idx);
					}




					vec.insert(vec.begin(), fsv);
				}
				}	
				int first_vec_size = vec.size() ;

				string  second_str = str.substr(ln, str.length() - ln);
				addvector(second_str);
				p = first_vec_size;
				p_lock = true;
			
		}
		else if (input.substr(0, 1).compare("c") == 0) {
			string c_str = input.substr(2, input.length() - 3);
			istringstream cs(c_str);
			string scb;
			vector <string> cv;
			bool cc = false;
			while (getline(cs, scb, ',')) {
				cv.push_back(scb);

			}
			for (int i = 0; i < vec.size(); i++) {
				while (vec.at(i).find(cv.front()) != string::npos) {
					cc = true;
					int c_word_idx = vec.at(i).find(cv.front());
					vec.at(i) =
						vec.at(i).substr(0, c_word_idx) + cv.back() + vec.at(i).substr(c_word_idx + cv.front().length(), vec.at(i).length() - c_word_idx - cv.front().length());
				}
			}
			if (cc == false) {
				notice = "there isnt " + cv.front();
				continue;
			}
			string m_str = "";
			for (int i = 0; i < vec.size(); i++) {
				m_str += vec.at(i);
			}
			str = m_str;
			vec.clear();
			addvector(str);
		}
		else if (input.substr(0, 1).compare("n") == 0) {
			if (p == vec.size() - 20) { notice = "The page is  last page"; }
			int stack_push = 0;
			p = p + 20;
			if (20 > vec.size() - p) {
				for (int kk = p - 20; kk < vec.size() - 20; kk++) {
					stack_push += vec.at(kk).length();
				}
				ln += stack_push;
				p = vec.size() - 20;
			}
			else {
				for (int k = p - 20; k < p; k++) {
					stack_push += vec.at(k).length();
				}
				ln += stack_push;


			}
		}
		else if (input.substr(0, 1).compare("p") == 0) {
			if (p == 0) { notice = "this page is first page!"; }
			if (p >= 20) {
				for (int i = p - 20; i < p; i++) {
					ln -= vec.at(i).length();
				}
				p -= 20;
			}
			else {
				ln = 0;
				p = 0;
				if (p_lock == true) {
					vec.clear();
					addvector(str);
				}
			}



		}
		else {
		notice = "please retry";
}
	}
		return 0;
	
}