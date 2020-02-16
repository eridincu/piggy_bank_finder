#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>

using namespace::std;


class MyGraph {
    //fields
    int BankCount = 0;
    int sccIndex = 0;
    int parentAmount = 0;

    vector<vector<int>> adjList;
    vector<vector<int>> scc;
    vector<bool> isChild;

    vector<int> inWhichScc;
    vector<int> inDegreeList;
    vector<int> index;
    vector<int> lowlink;
    vector<bool> onStack;

    stack<int> s;

    void initGraph(string _path) {

        ios_base::sync_with_stdio(false);
        ifstream infile;
        infile.open(_path);
        //read BankAmount
        infile >> BankCount;
        //init vector
        adjList = vector<vector<int>>(BankCount+1);

        for(int i = 1; i <=  BankCount; i++) {
            int numOfKeys = 0;
            infile >> numOfKeys;

            for(int j = 1; j <= numOfKeys; j++) {
                int whichKey = 0;
                infile >> whichKey;

                adjList[i].push_back(whichKey);
            }
        }
        infile.close();
    }

    void sccMaker(int v) {
        (index)[v] = indexNum;
        (lowlink)[v] = indexNum;
        indexNum++;
        s.push(v);
        (onStack)[v] = true;

        for(int i = 0; i < adjList[v].size(); i++) {
            int w = (adjList[v])[i];
            if((index)[w]==0) {
                sccMaker(w);
                lowlink[v] = min(lowlink[v],lowlink[w]);
            }
            else if((onStack)[w]) {
                (lowlink)[v] = min((lowlink)[v],(index)[w]);
            }
        }

        if((lowlink)[v]==(index)[v]) {
            vector<int> newScc;

            while(s.top()!=v) {
                int w = s.top();
                s.pop();
                (onStack)[w] = false;
                newScc.push_back(w);

                inWhichScc[w] = sccIndex;
            }
            int root = s.top();
            s.pop();
            newScc.push_back(root);
            inWhichScc[root] = sccIndex;
            (onStack)[root] = false;


            scc.push_back(newScc);
            sccIndex++;//
        }


    }
    //in progress
    void decideParents() {

        isChild = vector<bool>(scc.size());

        for(int i = 1; i <= BankCount; i++) {
            for(int adj : adjList[i]) {

                int inThatScc = inWhichScc[i];

                if(inWhichScc[adj]!=inThatScc) {
                    isChild[inWhichScc[adj]] = true;
                }
            }
        }
    }

public:

    int indexNum = 1;

    MyGraph(string _path) {
        initGraph(_path);
    }

    void process() {
        tarjan();
        decideParents();

    }
    void tarjan() {

        index = vector<int>(BankCount+1);
        lowlink = vector<int>(BankCount+1);
        onStack = vector<bool>(BankCount+1);
        inWhichScc = vector<int>(BankCount+1);

        for(int i = 1; i <= BankCount;i++) {
            if((index)[i]==0) {
                sccMaker(i);
            }
        }

    }

    void printParents(string _outputpath) {
        ofstream output(_outputpath);

        for(int i = 0; i < scc.size(); i++) {

            if(!isChild[i]) {
                parentAmount++;
            }
        }
        output << parentAmount << " ";


        for(int i = 0; i < scc.size(); i++) {

            if(!isChild[i]) {
                output << scc[i].front() << " ";
                parentAmount++;
            }
        }

        output.close();
    }
};



int main(int argc, char* argv[]) {
    if(argc != 3) {
        cout << "Run the code with the following command: ./project3 [input_file] [output_file]" << endl;
    }


    MyGraph *mygraph = new MyGraph(argv[1]);
    mygraph->process();

    mygraph->printParents(argv[2]);

    cout << " end." << endl;
    return 0;
}