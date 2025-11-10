# include <iostream>
# include <map>
# include <vector>
# include <algorithm>
# include <set>

using namespace std;

const int N = 100000;
int numberOfPeople = 0;
map<string, vector<string>> parents;
map<int, int> numberOfPeopleBornAt;
int maxUnrelatedPeople = 0; 
vector<pair<int, int>> numberOfPeopleBornAtArray; // Lưu {ngày sinh dạng số, số người}
int arraySize = 0;
vector<int> number(N, 0); // lưu số người
vector<int> dateInt(N, 0); // lưu ngày sinh dạng số
vector<int> prefix(N, 0); // tính prefix sum

vector<string> people;
map<string, int> dp0, dp1; // dp0[u]: số người lớn nhất không liên quan khi không nhận u vào đồ thị,  dp1[u]: số người lớn nhất không liên quan khi nhận u vào đồ thị
map<string, vector<string>> adj; // danh sách đỉnh kề
map<string, bool> visited;

int convertDateIntoInterger(string date) {
  int year = (date[0] - '0') * 1000 + (date[1] - '0') * 100 + (date[2] - '0') * 10 + (date[3] - '0');
  int month = (date[5] - '0') * 10 + (date[6] - '0');
  int day = (date[8] - '0') * 10 + (date[9] - '0');

  return year * 365 + month * 30 + day;
}


/*
  NUMBER_PEOPLE_BORN_BETWEEN
*/

// tìm chỉ số bắt đầu >= thời gian start
int getStartIndex(int start) {
  int startIndex = 0, l = 1, r = arraySize;

  while(l <= r) {
    int m = (l + r) / 2;

    if (dateInt[m] == start) {
      return m;
    } else if (dateInt[m] > start) {
      startIndex = m;
      r = m - 1;
    } else {
      l = m + 1;
    }
  }

  return startIndex;
}

// tìm chỉ số kết thúc <= thời gian end
int getEndIndex(int end) {
  int endIndex = 0, l = 1, r = arraySize;

  while(l <= r) {
    int m = (l + r) / 2;

    if (dateInt[m] == end) {
      return m;
    } else if (dateInt[m] < end) {
      endIndex = m;
      l = m + 1;
    } else {
      r = m - 1;
    }
  }

  return endIndex;
}

int calculateTotalPeople(string start, string end) {
  int intStart = convertDateIntoInterger(start);
  int intEnd = convertDateIntoInterger(end);
  int startIndex = getStartIndex(intStart);
  int endIndex = getEndIndex(intEnd);

  if (0 < startIndex && startIndex <= arraySize && 0 < endIndex && endIndex <= arraySize && startIndex <= endIndex) {
    return prefix[endIndex] - prefix[startIndex - 1];
  }

  return 0;
}


/*
  MOST_ALIVE_ANCESTOR
*/
int mostAliveAncestor(string child) {
  if (parents.find(child) == parents.end()) {
    return 0;
  }

  int result = 0;
  for (string p : parents[child]) {
    result = max(result, mostAliveAncestor(p) + 1);
  }

  return result;
}


/* 
  MAX_UNRELATED_PEOPLE
*/
void dfs(string u) {
  visited[u] = true;
  dp0[u] = 0; // không chọn u
  dp1[u] = 1; // chọn u

  for (string v : adj[u]) {
    if (visited[v] == false) {
      dfs(v); // đi duyệt các nút kề (nút kề là nút có thể là cha hoặc con của nút hiện tại)

      dp0[u] += max(dp0[v], dp1[v]); // không chọn u thì có thể chọn v hoặc không chọn v
      dp1[u] += dp0[v]; // chọn u thì không được chọn v
    }
  }
}


// input
void input() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  string child, date, father, mother, isAlive, regionchild;
  cin >> child;

  while(child != "*") {
    cin >> date >> father >> mother >> isAlive >> regionchild;

    int dateInt = convertDateIntoInterger(date);

    numberOfPeople ++;
    numberOfPeopleBornAt[dateInt] ++;
    people.push_back(child);

    if (father != "0000000") {
      parents[child].push_back(father);
      adj[child].push_back(father);
      adj[father].push_back(child);
    }
    
    if (mother != "0000000") {
      parents[child].push_back(mother);
      adj[child].push_back(mother);
      adj[mother].push_back(child);
    }

    cin >> child;
  }
}

// process
void process() {
  // Chuyển map {ngày sinh dạng số, số người} sang vector rồi sắp xếp theo ngày
  numberOfPeopleBornAtArray.push_back({0, 0}); // để cho chỉ số bắt đầu từ 1
  for (pair<int, int> p : numberOfPeopleBornAt) {
    numberOfPeopleBornAtArray.push_back(p);
    arraySize ++;
  }

  sort(numberOfPeopleBornAtArray.begin(), numberOfPeopleBornAtArray.end(), [](pair<int, int>& a, pair<int, int>& b) {
    return a.first < b.first;
  });

  // chuyển sang vector ngày sinh, số lượng người
  for (int i = 1; i <= arraySize; i++) {
    dateInt[i] = numberOfPeopleBornAtArray[i].first;
    number[i] = numberOfPeopleBornAtArray[i].second;
  }

  // tính prefix sum
  for (int i = 1; i <= arraySize; i++) {
    prefix[i] = prefix[i - 1] + number[i];
  }

  // Tính MAX_UNRELATED_PEOPLE
  for (string p : people) {
    visited[p] = false;
  }

  for (string p : people) {
    if (visited[p] == false) {
      dfs(p);

      maxUnrelatedPeople += max(dp0[p], dp1[p]);
    }
  }
}

// query 
void query() {
  string query, date, start, end, child;

  cin >> query;

  while(query != "*") {
    if (query == "NUMBER_PEOPLE") {
      cout << numberOfPeople << endl;
    } else if (query == "NUMBER_PEOPLE_BORN_AT") {
      cin >> date;
      int dateInt = convertDateIntoInterger(date);
      if (numberOfPeopleBornAt.find(dateInt) == numberOfPeopleBornAt.end()) {
        cout << 0 << endl;
      } else {
        cout << numberOfPeopleBornAt[dateInt] << endl;
      }
    } else if (query == "MAX_UNRELATED_PEOPLE") {
      cout << maxUnrelatedPeople << endl;
    } else if (query == "MOST_ALIVE_ANCESTOR") {
      cin >> child;
      cout << mostAliveAncestor(child) << endl;
    } else {
      cin >> start >> end;
      cout << calculateTotalPeople(start, end) << endl;
    }

    cin >> query;
  }
}

int main() {
  input();
  process();
  query();

  return 0;
}