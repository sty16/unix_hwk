#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<string>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<cmath>
using namespace std;

struct Track{
    int id;      // person id
    double x, y; // position range[0km, 200km]
    string date; // date YYYY-MM-DD
    string time; // time HH:MM
    Track(int _id, double _x, double _y, string & _date, string & _time) : id(_id), x(_x), y(_y), date(_date), time(_time) {}
};

struct Point{
    double x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

struct Person{
    int id;
    bool isInfected;
    Person(int _id, bool _isInfected) : id(_id), isInfected(_isInfected) {}
};

class Solution {
public:

    vector<Track> tracks;
    unordered_map<int, vector<Track>> mp;
    unordered_set<int> infected;
    static const int n = 100;    // 人数



    static bool cmp(Track &a, Track &b) {
        int t1 = time2int(a.date, a.time);
        int t2 = time2int(b.date, b.time);
        return t1 < t2;
    }

    static int time2int(string& date, string& time) {
        return  (stoi(date.substr(8, 2)) - 1) * 1440 + stoi(time.substr(0, 2)) * 60 + stoi(time.substr(3, 2));
    }

    vector<Track> getPersonTrack(int person_id, string date) {
        if(!mp.count(person_id)) {
            cout << "查无此人" << endl;
            return {};
        }
        string time = "23:59";
        int t = time2int(date, time);
        vector<Track> ans;
        for(auto a : mp[person_id]) {
            int tmp = time2int(a.date, a.time);
            if(tmp < t && t - tmp < 14 * 1440) ans.push_back(a);
        }
        return ans;
    }

    vector<int> getPersonWithinPlace(vector<Point>& base_station, vector<int>& infected_person, Point pos, string date) {
        simulation(base_station, infected_person, date);
        string time = "23:59";
        int t = time2int(date, time);
        vector<int> ans;
        for(int id : infected) {
            for(auto track : mp[id]) {
                int tmp = time2int(track.date, track.time);
                if(tmp < t && t - tmp < 1440) {
                    Point cur(track.x, track.y);
                    if(distance(cur, pos) < 1.0) {
                        ans.push_back(id);
                        break;
                    }
                }
            }
        }
        return ans;
    }

    // 给定基站的位置，并给定初始感染的人, 模拟传染过程
    // 采用滑动时间窗来判断 3个小时内 位于基站可见位置 并距离小于0.5km  可能感染。
    void simulation(vector<Point>& base_station, vector<int>& infected_person, string end_date="2020-09-30", string end_time="23:59") {
        string start_date = "2020-09-01";
        string start_time = "00:00";

        double threshold = 0.5;

        infected.clear();
        infected.insert(infected_person.begin(), infected_person.end());
        vector<Point> dangerPos;
        int begin = time2int(start_date, start_time);
        int end = time2int(end_date, end_time);

        for(int k = begin; k < end; k += 180) {
            // 记录感染的人去过的位置

            for(int id : infected) {
                for(auto track : mp[id]) {
                    int t = time2int(track.date, track.time);
                    if(t >= k && t < k + 180) {
                        dangerPos.emplace_back(track.x, track.y);
                    }
                }
            }

            // 判断健康的人是否可能被感染
            for(auto it = mp.begin(); it != mp.end(); ++it) {
                if(infected.count(it->first)) continue;
                for(auto track : mp[it->first]) {
                    if(infected.count(it->first)) break;
                    int t = time2int(track.date, track.time);
                    if(t >= k && t <= k + 180) {
                        Point cur(track.x, track.y);
                        for(auto pos : dangerPos) {
                            if(distance(pos, cur) < threshold) {
                                infected.insert(it->first);
                                break;
                            }
                        }
                    }
                }
            }
        }

    }

    double distance(Point& a, Point& b) {
        return sqrt(pow(abs(a.x - b.x), 2) + pow(abs(a.y - b.y), 2));
    }

    // 生成100个人，编号为0-99的随机坐标与时间数据 两个浮点数坐标范围为[0, 200] 日期格式为YYYY-MM-DD HH:MM
    void readDataFromFile(string file) {
        ifstream infile;
        infile.open(file, ios::in);
        string str;
        while(getline(infile, str)) {
            stringstream ss(str);
            int id;
            double x, y;
            string date, time;
            ss >> id >> x >> y >> date >> time;
            mp[id].emplace_back(id, x, y, date, time);
        }
        // 对每个人的轨迹按时间排序
        for(auto it = mp.begin(); it != mp.end(); ++it) {
            int id = it->first;
            sort(mp[id].begin(), mp[id].end(), cmp);
        }

        infile.close();
    }

    void writeData() {
        ofstream out;
        out.open("data.txt", ios::out);
        for (int i = 0; i < 100; ++i) {
            for (int j = 0; j < 200; ++j) {
                int id = i;
                double x = (double)(rand() / (double)RAND_MAX) * 200.0;
                double y = (double)(rand() / (double)RAND_MAX) * 200.0;
                string date = "2020-09-";
                string day = to_string(rand() % 31);
                day = day.size() < 2 ? "0" + day : day;
                date += day;
                string time = to_string(rand() % 24);
                if (time.size() < 2) time = "0" + time;
                string minute = to_string(rand() % 60);
                if (minute.size() < 2) minute = "0" + minute;
                time = time + ":" + minute;
                out << id << " " << x << " " << y << " " << date << " " << time << endl;
            }
        }
        out.close();
    }

};

int main() {
    Solution so;
    so.readDataFromFile("data.txt");
    string date = "2020-09-06";
    Point pos(191.7, 121.4);
    vector<int> initial_infected = {1, 2, 3, 5, 6, 23, 26, 56, 10, 100, 12, 14,15};
    vector<Point> base_station;
    base_station.emplace_back(10, 10);


    vector<Track> track = so.getPersonTrack(0, date);
    vector<int> infected = so.getPersonWithinPlace(base_station, initial_infected , pos, date);
    for(auto t : track) {
        cout << t.id << " " << t.x << " " << t.y << " " << t.date <<" " << t.time << endl; 
    }
    cout << "感染人id" << endl;
    for(int id : infected) {
        cout << id << endl;
    }
}