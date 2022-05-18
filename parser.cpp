#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;


struct Gold_Row{
    public:
        string date;
        double open;
        double high;
        double low;
        double close;
        int volume;
        string currency;
        
        Gold_Row () {}

        Gold_Row (double o, double h, double l, double c, int v, string cu, string d) : 
                    open{o},
                    high{h},
                    low{l},
                    close{c},
                    volume{v},
                    currency{cu},
                    date{d} {}
            
};

struct Gold{
private:
    vector<Gold_Row> data;
public:
    Gold() {
        string line;
        string word;
        Gold_Row row;
        fstream file ("gold.csv", ios::in);
        if(file.is_open()) {
            while(getline(file, line)) {   
                stringstream str(line);
                getline(str, word, ',');
                row.date = word;

                getline(str, word, ',');
                double xd = stod(word);
                row.open = xd;

                getline(str, word, ',');
                xd = stod(word);
                row.high = xd;

                getline(str, word, ',');
                xd = stod(word);
                row.low = xd;

                getline(str, word, ',');
                xd = stod(word);
                row.close = xd;
                
                getline(str, word, ',');
                int xd2 = stoi(word);
                row.volume = xd2;
                
                getline(str, word, ',');
                row.currency = word;

                data.push_back(row);
            }
        }
        else {
            cout<<"Could not open the file\n";
        }
    }

    void printRow(int i) {
        cout << (data[i]).date << " " << (data[i]).open << " " << (data[i]).high << " " << (data[i]).low << " " << (data[i]).close << " " << (data[i]).volume << " " << (data[i]).currency << endl;
    }
};

int main() {
    Gold gold;

    for(int i = 0; i < 10; i++) {
        gold.printRow(i); 
    }
}