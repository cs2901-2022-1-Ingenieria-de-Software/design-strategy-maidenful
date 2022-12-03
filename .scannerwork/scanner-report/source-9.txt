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
    int lines;
    vector<Gold_Row> data;
public:
    Gold() {
        lines = 0;
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
                lines++;
            }
        }
        else {
            cout<<"Could not open the file\n";
        }
    }

    void printRow(int i) {
        cout << (data[i]).date << " " << (data[i]).open << " " << (data[i]).high << " " << (data[i]).low << " " << (data[i]).close << " " << (data[i]).volume << " " << (data[i]).currency << endl;
    }

    Gold_Row getRow(int i) {
        return data[i];
    }

    int getSize() {
        return lines;
    }
};

class PredictionStrategy{
public:
    Gold * goldTable;
    
    virtual double calculatePrediction() = 0;

};

class AverageOpenPredictionStrategy : public PredictionStrategy{
public:
    AverageOpenPredictionStrategy(Gold* g){
        goldTable = g;
    };
    double calculatePrediction(){
        double result = 0;
        for(int i = 0; i < goldTable->getSize(); i++) {
            result =+ (goldTable->getRow(i)).open;
        }
        result = result / goldTable->getSize();
        return result;
        
    }
};

class AverageClosePredictionStrategy : public PredictionStrategy{
public:
    AverageClosePredictionStrategy(Gold* g){
        goldTable = g;
    };
    double calculatePrediction(){
        double result = 0;
        for(int i = 0; i < goldTable->getSize(); i++) {
            result =+ (goldTable->getRow(i)).close;
        }
        result = result / goldTable->getSize();
        return result;
    }
};

class HighValueMovingAveragePredictionStrategy : public PredictionStrategy{
public:
    HighValueMovingAveragePredictionStrategy(Gold* g){
        goldTable = g;
    };
    double calculatePrediction(){
        double result = 0;
        for(int i = goldTable->getSize() - 7; i < goldTable->getSize(); i++) {
            result =+ (goldTable->getRow(i)).close;
        }
        result = result / 7;
        return result;
    }

};

class Context{
private:
    PredictionStrategy * strategy;
public:
    void setStrategy(PredictionStrategy * S){
        strategy = S;
    }

    double executeStrategy(){
        return strategy->calculatePrediction();
    }

};

int main(){
    Context App;
    Gold data;

    while(true != false){
        cout << "Prediction Strategies:\n" << "(1) Average Open Prediction Strategy\n" << 
        "(2) Average Close Prediction Strategy\n" << "(3) 7 Day High Value Moving Average Prediction Strategy\n" <<
        "Select your prediction strategy:\n" << "(4) END\n";
        int i = 0;
        cin >> i;

        switch (i){
            case 1:
                App.setStrategy(new AverageOpenPredictionStrategy(&data));
                break;
            case 2:
                App.setStrategy(new AverageClosePredictionStrategy(&data));
                break;
            case 3:
                App.setStrategy(new HighValueMovingAveragePredictionStrategy(&data));
                break;
            default:
                return 0;
        }

        double prediction = App.executeStrategy();
        cout << "\nPrediction Result: " << prediction << " USD\n\n";
    }
}; 