#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <list>
#include <algorithm>
#include <climits>
#include <cmath>
#include <sstream>
#include <cctype>
using namespace std;

class Heap {
private:
    struct Node {
        string vname;
        string psf;
        int cost;
        
        bool operator<(const Node& other) const {
            return cost > other.cost; // Min heap
        }
    };
    
    priority_queue<Node> pq;
    
public:
    void add(const string& vname, const string& psf, int cost) {
        Node n;
        n.vname = vname;
        n.psf = psf;
        n.cost = cost;
        pq.push(n);
    }
    
    bool isEmpty() {
        return pq.empty();
    }
    
    void remove(string& vname, string& psf, int& cost) {
        Node n = pq.top();
        pq.pop();
        vname = n.vname;
        psf = n.psf;
        cost = n.cost;
    }
};

class Graph_M {
private:
    struct Vertex {
        unordered_map<string, int> nbrs;
    };
    
    unordered_map<string, Vertex> vtces;
    
    struct Pair {
        string vname;
        string psf;
        int min_dis;
        int min_time;
    };
    
public:
    Graph_M() {}
    
    int numVertex() {
        return vtces.size();
    }
    
    bool containsVertex(string vname) {
        return vtces.find(vname) != vtces.end();
    }
    
    void addVertex(string vname) {
        Vertex vtx;
        vtces[vname] = vtx;
    }
    
    void removeVertex(string vname) {
        Vertex vtx = vtces[vname];
        vector<string> keys;
        
        for (auto& pair : vtx.nbrs) {
            keys.push_back(pair.first);
        }
        
        for (string key : keys) {
            Vertex& nbrVtx = vtces[key];
            nbrVtx.nbrs.erase(vname);
        }
        
        vtces.erase(vname);
    }
    
    int numEdges() {
        int count = 0;
        for (auto& pair : vtces) {
            count += pair.second.nbrs.size();
        }
        return count / 2;
    }
    
    bool containsEdge(string vname1, string vname2) {
        if (vtces.find(vname1) == vtces.end() || vtces.find(vname2) == vtces.end()) {
            return false;
        }
        
        Vertex& vtx1 = vtces[vname1];
        return vtx1.nbrs.find(vname2) != vtx1.nbrs.end();
    }
    
    void addEdge(string vname1, string vname2, int value) {
        if (vtces.find(vname1) == vtces.end() || vtces.find(vname2) == vtces.end()) {
            return;
        }
        
        Vertex& vtx1 = vtces[vname1];
        Vertex& vtx2 = vtces[vname2];
        
        if (vtx1.nbrs.find(vname2) != vtx1.nbrs.end()) {
            return;
        }
        
        vtx1.nbrs[vname2] = value;
        vtx2.nbrs[vname1] = value;
    }
    
    void removeEdge(string vname1, string vname2) {
        if (vtces.find(vname1) == vtces.end() || vtces.find(vname2) == vtces.end()) {
            return;
        }
        
        Vertex& vtx1 = vtces[vname1];
        Vertex& vtx2 = vtces[vname2];
        
        if (vtx1.nbrs.find(vname2) == vtx1.nbrs.end()) {
            return;
        }
        
        vtx1.nbrs.erase(vname2);
        vtx2.nbrs.erase(vname1);
    }
    
    void display_Map() {
        cout << "\t Delhi Metro Map" << endl;
        cout << "\t------------------" << endl;
        cout << "----------------------------------------------------\n" << endl;
        
        for (auto& pair : vtces) {
            string str = pair.first + " =>\n";
            Vertex& vtx = pair.second;
            
            for (auto& nbrPair : vtx.nbrs) {
                str += "\t" + nbrPair.first + "\t";
                if (nbrPair.first.length() < 16)
                    str += "\t";
                if (nbrPair.first.length() < 8)
                    str += "\t";
                str += to_string(nbrPair.second) + "\n";
            }
            cout << str << endl;
        }
        cout << "\t------------------" << endl;
        cout << "---------------------------------------------------\n" << endl;
    }
    
    void display_Stations() {
        cout << "\n***********************************************************************\n" << endl;
        int i = 1;
        for (auto& pair : vtces) {
            cout << i << ". " << pair.first << endl;
            i++;
        }
        cout << "\n***********************************************************************\n" << endl;
    }
    
    bool hasPath(string vname1, string vname2, unordered_map<string, bool>& processed) {
        if (containsEdge(vname1, vname2)) {
            return true;
        }
        
        processed[vname1] = true;
        
        Vertex& vtx = vtces[vname1];
        
        for (auto& pair : vtx.nbrs) {
            string nbr = pair.first;
            if (processed.find(nbr) == processed.end()) {
                if (hasPath(nbr, vname2, processed)) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
    int dijkstra(string src, string des, bool nan) {
        int val = 0;
        unordered_map<string, pair<int, string>> map; // cost, psf
        Heap heap;
        
        for (auto& pair : vtces) {
            string key = pair.first;
            int cost = INT_MAX;
            string psf = "";
            
            if (key == src) {
                cost = 0;
                psf = key;
            }
            
            heap.add(key, psf, cost);
            map[key] = make_pair(cost, psf);
        }
        
        while (!heap.isEmpty()) {
            string rpVname, rpPsf;
            int rpCost;
            heap.remove(rpVname, rpPsf, rpCost);
            
            if (rpVname == des) {
                val = rpCost;
                break;
            }
            
            map.erase(rpVname);
            
            Vertex& v = vtces[rpVname];
            for (auto& nbrPair : v.nbrs) {
                string nbr = nbrPair.first;
                if (map.find(nbr) != map.end()) {
                    int oc = map[nbr].first;
                    int nc;
                    
                    if (nan)
                        nc = rpCost + 120 + 40 * nbrPair.second;
                    else
                        nc = rpCost + nbrPair.second;
                    
                    if (nc < oc) {
                        map[nbr].first = nc;
                        map[nbr].second = rpPsf + nbr;
                        heap.add(nbr, rpPsf + nbr, nc);
                    }
                }
            }
        }
        return val;
    }
    
    string Get_Minimum_Distance(string src, string dst) {
        int min = INT_MAX;
        string ans = "";
        unordered_map<string, bool> processed;
        list<Pair> stack;
        
        Pair sp;
        sp.vname = src;
        sp.psf = src + "  ";
        sp.min_dis = 0;
        sp.min_time = 0;
        
        stack.push_front(sp);
        
        while (!stack.empty()) {
            Pair rp = stack.front();
            stack.pop_front();
            
            if (processed.find(rp.vname) != processed.end()) {
                continue;
            }
            
            processed[rp.vname] = true;
            
            if (rp.vname == dst) {
                int temp = rp.min_dis;
                if (temp < min) {
                    ans = rp.psf;
                    min = temp;
                }
                continue;
            }
            
            Vertex& rpvtx = vtces[rp.vname];
            
            for (auto& nbrPair : rpvtx.nbrs) {
                string nbr = nbrPair.first;
                if (processed.find(nbr) == processed.end()) {
                    Pair np;
                    np.vname = nbr;
                    np.psf = rp.psf + nbr + "  ";
                    np.min_dis = rp.min_dis + nbrPair.second;
                    stack.push_front(np);
                }
            }
        }
        ans += to_string(min);
        return ans;
    }
    
    string Get_Minimum_Time(string src, string dst) {
        int min = INT_MAX;
        string ans = "";
        unordered_map<string, bool> processed;
        list<Pair> stack;
        
        Pair sp;
        sp.vname = src;
        sp.psf = src + "  ";
        sp.min_dis = 0;
        sp.min_time = 0;
        
        stack.push_front(sp);
        
        while (!stack.empty()) {
            Pair rp = stack.front();
            stack.pop_front();
            
            if (processed.find(rp.vname) != processed.end()) {
                continue;
            }
            
            processed[rp.vname] = true;
            
            if (rp.vname == dst) {
                int temp = rp.min_time;
                if (temp < min) {
                    ans = rp.psf;
                    min = temp;
                }
                continue;
            }
            
            Vertex& rpvtx = vtces[rp.vname];
            
            for (auto& nbrPair : rpvtx.nbrs) {
                string nbr = nbrPair.first;
                if (processed.find(nbr) == processed.end()) {
                    Pair np;
                    np.vname = nbr;
                    np.psf = rp.psf + nbr + "  ";
                    np.min_time = rp.min_time + 120 + 40 * nbrPair.second;
                    stack.push_front(np);
                }
            }
        }
        double minutes = ceil((double)min / 60);
        ans += to_string(minutes);
        return ans;
    }
    
    vector<string> get_Interchanges(string str) {
        vector<string> arr;
        vector<string> res;
        
        stringstream ss(str);
        string token;
        while (ss >> token) {
            if (!token.empty())
                res.push_back(token);
        }
        
        arr.push_back(res[0]);
        int count = 0;
        
        for (int i = 1; i < res.size() - 1; i++) {
            int index = res[i].find('~');
            string s = res[i].substr(index + 1);
            
            if (s.length() == 2) {
                string prev = res[i - 1].substr(res[i - 1].find('~') + 1);
                string next = res[i + 1].substr(res[i + 1].find('~') + 1);
                
                if (prev == next) {
                    arr.push_back(res[i]);
                } else {
                    arr.push_back(res[i] + " ==> " + res[i + 1]);
                    i++;
                    count++;
                }
            } else {
                arr.push_back(res[i]);
            }
        }
        arr.push_back(to_string(count));
        arr.push_back(res[res.size() - 1]);
        return arr;
    }
    
    vector<string> getKeys() {
        vector<string> keys;
        for (auto& pair : vtces) {
            keys.push_back(pair.first);
        }
        return keys;
    }
    
    static void Create_Metro_Map(Graph_M& g) {
        // Blue Line (Line 1) - Dakshineswar to Kavi Subhash
        g.addVertex("Dakshineswar~B");
        g.addVertex("Baranagar~BP");
        g.addVertex("Noapara~BY");
        g.addVertex("Dum Dum~B");
        g.addVertex("Belgachia~B");
        g.addVertex("Shyambazar~B");
        g.addVertex("Sovabazar~B");
        g.addVertex("Girish Park~B");
        g.addVertex("Mahatma Gandhi Road~B");
        g.addVertex("Central~B");
        g.addVertex("Chandni Chowk~B");
        g.addVertex("Esplanade~BGP");
        g.addVertex("Park Street~BP");
        g.addVertex("Maidan~B");
        g.addVertex("Rabindra Sadan~B");
        g.addVertex("Netaji Bhawan~B");
        g.addVertex("Jatin Das Park~B");
        g.addVertex("Kalighat~B");
        g.addVertex("Rabindra Sarobar~B");
        g.addVertex("Mahanayak Uttam Kumar~B");
        g.addVertex("Netaji~B");
        g.addVertex("Masterda Surya Sen~B");
        g.addVertex("Gitanjali~B");
        g.addVertex("Kavi Nazrul~B");
        g.addVertex("Shahid Khudiram~B");
        g.addVertex("Kavi Subhash~BO");
        
        // Green Line (Line 2) - Howrah Maidan to Salt Lake Sector V
        g.addVertex("Howrah Maidan~G");
        g.addVertex("Howrah~G");
        g.addVertex("Mahakaran~G");
        g.addVertex("Sealdah~G");
        g.addVertex("Phoolbagan~G");
        g.addVertex("Salt Lake Stadium~G");
        g.addVertex("Salt Lake Sector V~GO");
        
        // Orange Line (Line 6) - Kavi Subhash to Hemanta Mukhopadhyay
        g.addVertex("Kavi Subhash~BO");
        g.addVertex("Hemanta Mukhopadhyay~O");
        g.addVertex("Kavi Nazrul~O");
        g.addVertex("City Centre~O");
        g.addVertex("Central Park~O");
        g.addVertex("IT Centre~OG");
        g.addVertex("Rabindra Tirtha~O");
        g.addVertex("VIP Bazar~O");
        g.addVertex("Beleghata~O");
        
        // Purple Line (Line 3) - Joka to Majerhat
        g.addVertex("Joka~P");
        g.addVertex("Thakurpukur~P");
        g.addVertex("Sakher Bazar~P");
        g.addVertex("Behala Chowrasta~P");
        g.addVertex("Behala Bazar~P");
        g.addVertex("Taratala~P");
        g.addVertex("Majerhat~P");
        
        // Yellow Line (Line 5) - Noapara to Jai Hind
        g.addVertex("Noapara~BY");
        g.addVertex("Baranagar~BP");
        g.addVertex("Biman Bandar~YO");
        g.addVertex("Jai Hind~YO");
        
        // Blue Line Edges
        g.addEdge("Dakshineswar~B", "Baranagar~BP", 2);
        g.addEdge("Baranagar~BP", "Noapara~BY", 2);
        g.addEdge("Noapara~BY", "Dum Dum~B", 2);
        g.addEdge("Dum Dum~B", "Belgachia~B", 1);
        g.addEdge("Belgachia~B", "Shyambazar~B", 1);
        g.addEdge("Shyambazar~B", "Sovabazar~B", 1);
        g.addEdge("Sovabazar~B", "Girish Park~B", 1);
        g.addEdge("Girish Park~B", "Mahatma Gandhi Road~B", 1);
        g.addEdge("Mahatma Gandhi Road~B", "Central~B", 1);
        g.addEdge("Central~B", "Chandni Chowk~B", 1);
        g.addEdge("Chandni Chowk~B", "Esplanade~BGP", 1);
        g.addEdge("Esplanade~BGP", "Park Street~BP", 1);
        g.addEdge("Park Street~BP", "Maidan~B", 1);
        g.addEdge("Maidan~B", "Rabindra Sadan~B", 1);
        g.addEdge("Rabindra Sadan~B", "Netaji Bhawan~B", 1);
        g.addEdge("Netaji Bhawan~B", "Jatin Das Park~B", 1);
        g.addEdge("Jatin Das Park~B", "Kalighat~B", 1);
        g.addEdge("Kalighat~B", "Rabindra Sarobar~B", 1);
        g.addEdge("Rabindra Sarobar~B", "Mahanayak Uttam Kumar~B", 2);
        g.addEdge("Mahanayak Uttam Kumar~B", "Netaji~B", 1);
        g.addEdge("Netaji~B", "Masterda Surya Sen~B", 1);
        g.addEdge("Masterda Surya Sen~B", "Gitanjali~B", 1);
        g.addEdge("Gitanjali~B", "Kavi Nazrul~B", 1);
        g.addEdge("Kavi Nazrul~B", "Shahid Khudiram~B", 1);
        g.addEdge("Shahid Khudiram~B", "Kavi Subhash~BO", 1);
        
        // Green Line Edges
        g.addEdge("Howrah Maidan~G", "Howrah~G", 1);
        g.addEdge("Howrah~G", "Mahakaran~G", 2);
        g.addEdge("Mahakaran~G", "Esplanade~BGP", 3);
        g.addEdge("Esplanade~BGP", "Sealdah~G", 2);
        g.addEdge("Sealdah~G", "Phoolbagan~G", 1);
        g.addEdge("Phoolbagan~G", "Salt Lake Stadium~G", 2);
        g.addEdge("Salt Lake Stadium~G", "Salt Lake Sector V~GO", 2);
        
        // Orange Line Edges
        g.addEdge("Kavi Subhash~BO", "Hemanta Mukhopadhyay~O", 2);
        g.addEdge("Hemanta Mukhopadhyay~O", "Kavi Nazrul~O", 1);
        g.addEdge("Kavi Nazrul~O", "City Centre~O", 2);
        g.addEdge("City Centre~O", "Central Park~O", 1);
        g.addEdge("Central Park~O", "IT Centre~OG", 2);
        g.addEdge("IT Centre~OG", "Salt Lake Sector V~GO", 1);
        g.addEdge("IT Centre~OG", "Rabindra Tirtha~O", 2);
        g.addEdge("Rabindra Tirtha~O", "VIP Bazar~O", 2);
        g.addEdge("VIP Bazar~O", "Beleghata~O", 1);
        
        // Purple Line Edges
        g.addEdge("Joka~P", "Thakurpukur~P", 2);
        g.addEdge("Thakurpukur~P", "Sakher Bazar~P", 1);
        g.addEdge("Sakher Bazar~P", "Behala Chowrasta~P", 1);
        g.addEdge("Behala Chowrasta~P", "Behala Bazar~P", 1);
        g.addEdge("Behala Bazar~P", "Taratala~P", 2);
        g.addEdge("Taratala~P", "Majerhat~P", 2);
        g.addEdge("Majerhat~P", "Park Street~BP", 3);
        g.addEdge("Park Street~BP", "Esplanade~BGP", 1);
        
        // Yellow Line Edges
        g.addEdge("Noapara~BY", "Biman Bandar~YO", 3);
        g.addEdge("Biman Bandar~YO", "Jai Hind~YO", 1);
        g.addEdge("Jai Hind~YO", "Beleghata~O", 2);
    }
    
    vector<string> printCodelist() {
        cout << "List of station along with their codes:\n" << endl;
        vector<string> keys = getKeys();
        vector<string> codes(keys.size());
        int i = 1, m = 1;
        
        for (int idx = 0; idx < keys.size(); idx++) {
            string key = keys[idx];
            string code = "";
            stringstream ss(key);
            string temp;
            
            while (ss >> temp) {
                int j = 0;
                char c = temp[0];
                while (j < temp.length() && c >= '0' && c <= '9') {
                    code += c;
                    j++;
                    if (j < temp.length())
                        c = temp[j];
                }
                if (j < temp.length() && (c < '0' || c > '9') && c < 123) {
                    code += c;
                }
            }
            
            if (code.length() < 2 && temp.length() > 1) {
                code += toupper(temp[1]);
            }
            
            codes[idx] = code;
            
            cout << i << ". " << key << "\t";
            if (key.length() < (22 - m))
                cout << "\t";
            if (key.length() < (14 - m))
                cout << "\t";
            if (key.length() < (6 - m))
                cout << "\t";
            cout << codes[idx] << endl;
            
            i++;
            if (i == (int)pow(10, m))
                m++;
        }
        return codes;
    }
};

int main() {
    Graph_M g;
    Graph_M::Create_Metro_Map(g);
    
    cout << "\n\t\t\t****WELCOME TO THE METRO APP*****" << endl;
    
    while (true) {
        cout << "\t\t\t\t~~LIST OF ACTIONS~~\n\n" << endl;
        cout << "1. LIST ALL THE STATIONS IN THE MAP" << endl;
        cout << "2. SHOW THE METRO MAP" << endl;
        cout << "3. GET SHORTEST DISTANCE FROM A 'SOURCE' STATION TO 'DESTINATION' STATION" << endl;
        cout << "4. GET SHORTEST TIME TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION" << endl;
        cout << "5. GET SHORTEST PATH (DISTANCE WISE) TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION" << endl;
        cout << "6. GET SHORTEST PATH (TIME WISE) TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION" << endl;
        cout << "7. EXIT THE MENU" << endl;
        cout << "\nENTER YOUR CHOICE FROM THE ABOVE LIST (1 to 7) : ";
        
        int choice = -1;
        cin >> choice;
        cin.ignore();
        
        cout << "\n***********************************************************\n" << endl;
        
        if (choice == 7) {
            break;
        }
        
        switch (choice) {
            case 1:
                g.display_Stations();
                break;
            
            case 2:
                g.display_Map();
                break;
            
            case 3: {
                vector<string> keys = g.getKeys();
                vector<string> codes = g.printCodelist();
                cout << "\n1. TO ENTER SERIAL NO. OF STATIONS\n2. TO ENTER CODE OF STATIONS\n3. TO ENTER NAME OF STATIONS\n" << endl;
                cout << "ENTER YOUR CHOICE:" << endl;
                int ch;
                cin >> ch;
                cin.ignore();
                
                string st1 = "", st2 = "";
                cout << "ENTER THE SOURCE AND DESTINATION STATIONS" << endl;
                
                if (ch == 1) {
                    int idx1, idx2;
                    cin >> idx1 >> idx2;
                    cin.ignore();
                    st1 = keys[idx1 - 1];
                    st2 = keys[idx2 - 1];
                } else if (ch == 2) {
                    string a, b;
                    getline(cin, a);
                    transform(a.begin(), a.end(), a.begin(), ::toupper);
                    int j;
                    for (j = 0; j < keys.size(); j++) {
                        if (a == codes[j])
                            break;
                    }
                    st1 = keys[j];
                    
                    getline(cin, b);
                    transform(b.begin(), b.end(), b.begin(), ::toupper);
                    for (j = 0; j < keys.size(); j++) {
                        if (b == codes[j])
                            break;
                    }
                    st2 = keys[j];
                } else if (ch == 3) {
                    getline(cin, st1);
                    getline(cin, st2);
                } else {
                    cout << "Invalid choice" << endl;
                    return 0;
                }
                
                unordered_map<string, bool> processed;
                if (!g.containsVertex(st1) || !g.containsVertex(st2) || !g.hasPath(st1, st2, processed)) {
                    cout << "THE INPUTS ARE INVALID" << endl;
                } else {
                    cout << "SHORTEST DISTANCE FROM " << st1 << " TO " << st2 << " IS " 
                         << g.dijkstra(st1, st2, false) << "KM\n" << endl;
                }
                break;
            }
            
            case 4: {
                cout << "ENTER THE SOURCE STATION: ";
                string sat1;
                getline(cin, sat1);
                cout << "ENTER THE DESTINATION STATION: ";
                string sat2;
                getline(cin, sat2);
                
                cout << "SHORTEST TIME FROM (" << sat1 << ") TO (" << sat2 << ") IS " 
                     << g.dijkstra(sat1, sat2, true) / 60 << " MINUTES\n\n" << endl;
                break;
            }
            
            case 5: {
                cout << "ENTER THE SOURCE AND DESTINATION STATIONS" << endl;
                string s1, s2;
                getline(cin, s1);
                getline(cin, s2);
                
                unordered_map<string, bool> processed2;
                if (!g.containsVertex(s1) || !g.containsVertex(s2) || !g.hasPath(s1, s2, processed2)) {
                    cout << "THE INPUTS ARE INVALID" << endl;
                } else {
                    vector<string> str = g.get_Interchanges(g.Get_Minimum_Distance(s1, s2));
                    int len = str.size();
                    cout << "SOURCE STATION : " << s1 << endl;
                    cout << "DESTINATION STATION : " << s2 << endl;
                    cout << "DISTANCE : " << str[len - 1] << endl;
                    cout << "NUMBER OF INTERCHANGES : " << str[len - 2] << endl;
                    cout << "~~~~~~~~~~~~~" << endl;
                    cout << "START  ==>  " << str[0] << endl;
                    for (int i = 1; i < len - 3; i++) {
                        cout << str[i] << endl;
                    }
                    cout << str[len - 3] << "   ==>    END" << endl;
                    cout << "~~~~~~~~~~~~~" << endl;
                }
                break;
            }
            
            case 6: {
                cout << "ENTER THE SOURCE STATION: ";
                string ss1;
                getline(cin, ss1);
                cout << "ENTER THE DESTINATION STATION: ";
                string ss2;
                getline(cin, ss2);
                
                unordered_map<string, bool> processed3;
                if (!g.containsVertex(ss1) || !g.containsVertex(ss2) || !g.hasPath(ss1, ss2, processed3)) {
                    cout << "THE INPUTS ARE INVALID" << endl;
                } else {
                    vector<string> str = g.get_Interchanges(g.Get_Minimum_Time(ss1, ss2));
                    int len = str.size();
                    cout << "SOURCE STATION : " << ss1 << endl;
                    cout << "DESTINATION STATION : " << ss2 << endl;
                    cout << "TIME : " << str[len - 1] << " MINUTES" << endl;
                    cout << "NUMBER OF INTERCHANGES : " << str[len - 2] << endl;
                    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                    cout << "START  ==>  " << str[0] << " ==>  ";
                    for (int i = 1; i < len - 3; i++) {
                        cout << str[i] << endl;
                    }
                    cout << str[len - 3] << "   ==>    END" << endl;
                    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                }
                break;
            }
            
            default:
                cout << "Please enter a valid option! " << endl;
                cout << "The options you can choose are from 1 to 7. " << endl;
        }
    }
    
    return 0;
}