#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

////////////////////////////‘”Ќ ÷»»//////////////////////////////////////////////
string DEHASH(vector <char> chars, vector <string> codes,string line);
string HASH(vector <char> chars, vector <string> codes,string line);
void Tree(vector<vector<int>> main, int head,string code = "");//код дл€ символа(вектор(бинарное дерево(BinaryTree)),корень -> --)
void SortTwoVec(vector <char> &set, vector <int> &count);// сортирует два массива(вектор, вектор -> ---)
vector <vector <int>> BinaryTree(vector <int> &count);// строит бинарное дерево дл€ ’ј‘‘ћјЌј(вектор -> вектор)
void WriteToFile(string line,string nameFile);
vector <string> split(string str, char ch);
string translateToByteString(string line);
string ReadingFileForDecrypt(string file);
string translateToNewString(string line);
void SortOneVec(vector <int> &count);// сортирует массив(вектор -> ---)
string makeByte(string binaryCode,int mode = 0);
string ReadingFile(string file);//—читывает содержимое файла(input:им€ файла, output:содержимое файла).
string intToBinary(int number);
int binaryToInt(string bin);
int size(string str);// длина строки(строка -> длина строки)
template <typename T1>
vector <T1> Reverse(vector <T1> count);// переворачивает массив/вектор (вектор -> ---)
template<typename T>
int FindIndex(vector <T> &set, T chr);// находит индекс в векторе по значению(вектор, значение -> индекс)

template <typename T2>
bool check(vector <T2> vec,T2 value);// провер€ет наличие символа в массиве/векторе(вектор, значение -> bool)
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////√ЋќЅјЋ№Ќџ≈ ѕ≈–≈ћ≈ЌЌџ≈////////////////////////////////////////////
vector <char> set;// символы
vector <int> count;// кол-во символов
vector<vector<int>> main1;//дл€ рекурсии и прохождению по дереву 
vector<char> vChar;// символы
vector<string> vCode;// коды символов
//////////////////////////////////////////////////////////////////////////

int main(){
	setlocale(LC_ALL,"RUS");
	string nameR;string nameW;
	char one;
	cout << "name file for read: ";
	cin >> nameR;
	cout << "name file for write: ";
	cin >> nameW;
	cout << "encrypt(e) or decrypt(anything): ";
	cin >> one;
	cout << endl;

	
/////////////////////////////////////////////////////
	if (one == 'e'){
		string line = ReadingFile(nameR);
		for(int i = 0; i < size(line); i++){
			if(!(check(set,line[i]))){
				set.push_back(line[i]);
				count.push_back(0);
			}
		}
		for (int i = 0; i < size(line); i++){
			count[FindIndex(set,line[i])]++;
		}

		SortTwoVec(set,count);
		vector <vector <int>> treeArr = BinaryTree(count);
		main1 = treeArr;
		int lastTreeArr =treeArr.size()-1;
		int root = treeArr[lastTreeArr][0]+treeArr[lastTreeArr][1];
		Tree(treeArr,root);
		cout<<"keyT->";
		for(int i = 0;i<vCode.size();i++){
			cout<<vChar[i]<<"~"<<vCode[i]<<"|";
		}
		cout<<endl;
		string inBin = HASH(vChar, vCode, line);
		string BinInByte = makeByte(inBin);
		string result = translateToNewString(BinInByte);
		WriteToFile(result, nameW);
		cout<<"successful"<< endl;
	}
	else{
		string ByteLine = ReadingFileForDecrypt(nameR);
		string keyFirst;
		string keySecond;
		string Key;
		cout<<"key: ";
		cin>>keyFirst;
		getline(cin,keySecond);
		Key = keyFirst + keySecond;
		
		vector <string> s = split(Key,'|');
		for (string i: s){
			vector <string> s2 = split(i,'~');
			vChar.push_back(s2[0][0]);
			vCode.push_back(s2[1]);
			//cout<<s2[0][0]<<" : "<<s2[1]<<",";
		}
		string inString = DEHASH(vChar, vCode, ByteLine);
		
		WriteToFile(inString, nameW);
		cout<<"successful"<< endl;
	}
	
	

	return 0;
}








//////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T>
vector <T> Reverse(vector <T> count){
	int iMinus = count.size();
	vector <T> reverse(iMinus);iMinus--;
	for(int i = count.size()-1; i >= 0; i--){
		reverse[iMinus-i] = count[i];
	}
	return reverse;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector <vector <int>> BinaryTree(vector <int> &count){
	vector <vector <int>> Tree;
	vector <vector <int>> Tree2;
	Tree.push_back(count);
	for(int i = 1; i < count.size(); i++){
		vector <int> vec2;
		vec2.push_back(Tree[i-1][0]);
		vec2.push_back(Tree[i-1][1]);
		Tree2.push_back(vec2);
		vector <int> vec;
		Tree.push_back(vec);
		Tree[i].push_back(Tree[i-1][0]+Tree[i-1][1]);
		//cout<<"["<<Tree[i-1][0]<<", "<<Tree[i-1][1]<<"]"<<endl;
		for(int r = 2; r < Tree[i-1].size();r++){
			Tree[i].push_back(Tree[i-1][r]);
		}
		SortOneVec(Tree[i]);
	}
	return Tree2;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ReadingFile(string file){
	ifstream fin(file);
	string str;
	string allText = "";
	int count = 0;
	string Line = "";
	while(!fin.eof()){
		//getline(fin,str);
		char s = fin.get();
		if (s=='\n'){
			allText += " ";
			continue;
		}
		allText += s;
		
	}
	fin.close();
	return allText;
}
string ReadingFileForDecrypt(string file){
	ifstream fin(file,ios_base::binary);
	string result = "";
	while(!fin.eof()){
		
		int num = fin.get();
		if (num < 0){
			result += makeByte(intToBinary(256+num),1);
		}
		else{
			result += makeByte(intToBinary(num),1);
		}
		
	}
	fin.close();
	return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
int FindIndex(vector <T> &set, T chr){
	for(int i = 0; i < set.size();i++){
		if(set[i] == chr) return i;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SortTwoVec(vector <char> &set, vector <int> &count){
	bool CHECK = false;
	for(int i = count.size()/2; i!=0;){
		for(int r = 0;r+i<count.size();r++){
			if (count[r]>count[r+i]){
				int safeInt = count[r];
				char safeChar = set[r];

				count[r] = count[r+i];
				set[r] = set[r+i];

				count[r+i] = safeInt;
				set[r+i] = safeChar;
				CHECK = true;
			}
		}
		if (!CHECK){
			i /= 2;
		}
		CHECK = false;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SortOneVec(vector <int> &count){
	bool CHECK = false;
	for(int i = count.size()/2; i!=0;){
		for(int r = 0;r+i<count.size();r++){
			if (count[r]>count[r+i]){
				int safeInt = count[r];

				count[r] = count[r+i];

				count[r+i] = safeInt;
				CHECK = true;
			}
		}
		if (!CHECK){
			i /= 2;
		}
		CHECK = false;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
int size(string str){
	int i = 0;
	while(true){
		if (str[i] == '\0'){
			return i;
		}
		i++;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T2>
bool check(vector <T2> vec,T2 value){
	for(int i = 0; i < vec.size(); i++){
		if(vec[i] == value) return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Tree(vector<vector<int>> main, int head,string code){
	

	vector <vector<int>> r = Reverse(main);
	//cout<< head<<endl;
	for(int I = 0;I<r.size();I++){
		//cout<<i[1]<<" -> "<<r[0]<<", "<<r[1]<<endl;
		if(head == r[I][0]+r[I][1]){
			//cout<<1;
			//cout<<i[1]<<" -> "<<r[0]<<", "<<r[1]<<endl;
			for(int i = 0; i < 2;i++){
				vector<vector<int>> mainC = main1;
				
				if (i == 0){
					Tree(mainC,r[I][i],code+"0");
				}
				else{
					Tree(mainC,r[I][i],code+"1");
				}
			}
		main1.erase(main1.begin() + FindIndex(main1,r[I]));
		//cout<<r[I][0]<<", "<<r[I][1]<<endl;
		return;

		}
	}
	vCode.push_back(code);
	int index = FindIndex(count,head);
	vChar.push_back(set[index]);

	set.erase(set.begin() + index);
	count.erase(count.begin() + index);

	return;
}
string HASH(vector <char> chars, vector <string> codes,string line){
	string HASHLine = "";
	for(int i = 0; i < size(line); i++){
		HASHLine += codes[FindIndex(chars,line[i])];
	}
	return HASHLine;
}
string DEHASH(vector <char> chars, vector <string> codes,string line){
	string HASHLine = "";
	string ForCheck = "";
	for(int i = 0; i < size(line); i++){
		ForCheck += line[i];
		if (check(codes,ForCheck)){
			HASHLine+=chars[FindIndex(codes,ForCheck)];
			ForCheck = "";
		}
	}
	return HASHLine;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
int binaryToInt(string bin) {
    int result = 0;
    int index = 1;
    for (int i = size(bin)-1;i>-1;i--){
    	if(bin[i] == '1'){
    		result+=index;
    	}
    index *=2;    	
    }
    return result;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
string intToBinary(int number) {
    string result = "";
    int index = 1;
    while(number>=2){
    int tVar = number%2;
    number = (number-tVar)/2;
    if(tVar == 1){
    	result = "1" + result;
    }
    else{
    	result = "0" + result;
    }
    }
    if(number == 1){
    	result = "1" + result;
    }
    else{
    	result = "0" + result;
    }
    return result;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
string makeByte(string binaryCode,int mode) {
int howlongZero = 8-(size(binaryCode)%8);
if (howlongZero==8){
	return binaryCode;
}
for(int i = 0;i<howlongZero;i++){
	if (mode == 0){
		binaryCode+="0";
	}
	else{
		binaryCode= "0" + binaryCode;
	}
	
}
return binaryCode;
}
vector <string> split(string str, char ch){
	vector <string> Return;
	string safe = "";
	for (int i = 0;i<size(str);i++){
		if (str[i] == ch){
			Return.push_back(safe);
			safe = "";
			continue;
		}
		safe += str[i];
	}
	if (size(safe) != 0){
		Return.push_back(safe);
	}
	return Return;
}
void WriteToFile(string line,string nameFile){
	ofstream outputFile(nameFile);
	outputFile<<line;
	outputFile.close();
}
string translateToNewString(string line){
	int howlongBytes = size(line) / 8;
	string result;

	for(int i = 0;i < howlongBytes; i++){
		string l;
		for (int r = 0; r<8; r++){
			l+=line[(i*8)+r];
		}
		result += (char) (binaryToInt(l));
	}
	return result;
}