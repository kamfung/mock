#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <cstring>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) {val = x; next = nullptr;}
};

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int v) {val = v; left = nullptr; right = nullptr;}
};
//[ 1, 3, 3,3, 4] , return ( 2, 3, 4) (1, 3, 4), (1, 2, 4)

vector<int> FindLargestSum(const vector<int>& nums) {
    vector<int> result;
    while (result.size() < 3) {
        int maxSoFarIdx = -1;
        for (int i = 0; i < nums.size(); i++) {
            if (find(result.begin(), result.end(), i) == result.end()) {
                if (maxSoFarIdx == -1 || nums[maxSoFarIdx] < nums[i]) {
                    maxSoFarIdx = i;
                }
            }
        }
        result.push_back(maxSoFarIdx);
    }
    sort(result.begin(), result.end());
    return result;
}
// priority_queue<int, vector<int>, less<int>> q;
int FindMinSlots(const vector<char> &tasks, int k) {
  map<char, int> taskCnt;
  for (char c: tasks) {
    taskCnt[c] ++;
  }
  priority_queue<int> pq;
  for (auto p: taskCnt) {
    pq.push(p.second);
  }
  int res = 0;
  while (!pq.empty()){
    vector<int> v;
    for (int i = 0; i <= k; i ++) {
      if (!pq.empty()) {
        int left = pq.top() - 1;
        if (left > 0) {
          v.push_back(left);
        }
        pq.pop();
        res ++;
      } else if (!v.empty()) {
        res ++;
      }
    }
    for(auto n: v) {
      pq.push(n);
    }
  }
  return res;
}

string minWindow(string s, string t) {
  vector<int> lookup(128); // outstanding chars I needed to match t
  int lent = t.length();
  int cnt = lent; // the number of outstanding chars to match t;
  int lens = s.length();
  int minlen = lens + 1;
  string res;
  for (char c: t) {
    lookup[c] ++;
  }
  int right = 0;
  
  for (int left = 0; left < lens; left ++) {
    if (left > 0) {
      if (++lookup[s[left - 1]] > 0) {
        cnt ++;
      }
    }
    while (right < lens && cnt > 0) {
      if (--lookup[s[right]] >= 0) { 
        cnt --;
      }
      right++;
    }

    if (cnt == 0 && (right - left) < minlen) {
      minlen = (right - left);
      res = s.substr(left, minlen);
    }
  }
  return res;
}

vector<int> getProduct(const vector<int>& nums)
{
    int n = nums.size();
    vector<int> v1(n, 1);
    vector<int> v2(n, 1);
    for (int i = 1; i < n; i ++) {
        v1[i] = nums[i - 1] * v1[i - 1];
    }
    for (int i = n - 2; i >= 0; i --) {
        v2[i] = nums[i + 1] * v2[i + 1];
    }
    for (int i = 0; i < n; i ++) {
        v1[i] *= v2[i];
    }
    return v1;
}

vector<vector<int>> threeSum(vector<int> & nums)
{
    int n = nums.size();
    sort(nums.begin(),nums.end());
    vector<vector<int>> res;
    for (int i = 0; i < n - 2; i ++) {
        if (i > 0 && nums[i] == nums[i - 1]){
            continue;
        }
        int left = i + 1;
        int right = n - 1;
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == 0) {
                res.push_back({nums[i], nums[left], nums[right]});
                left ++;
                while (left < right && nums[left] == nums[left - 1]) {
                    left ++;
                }
                right --;
            } else if (sum < 0) {
                left ++;
            } else {
                right --;  
            } 
        }
    }
    return res;
}

/*
[-1, 0, 1, 2, -1, -4],
[-4, -1, -1, 0, 1, 2]
[2 -1 -1 -1 -1 -1 -1],
*/
bool validStr(const string& str) {
  stack<char> s;
  for (size_t i = 0; i < str.size(); i++) {
    if (str[i] == '(') s.push(str[i]);
    else if (str[i] == ')') {
      if (s.empty() || s.top() != '(') {
        return false;
      }
      s.pop();
    }
  }
  return s.empty();
}

vector<string> getValidStrings(string str) {
  queue<string>  q;
  vector<string> result;
  bool           foundFirstValid = false;

  q.push(str);
  while (!q.empty() && !foundFirstValid) {
    unordered_set<string> lookup;
    size_t n = q.size();
    for (size_t i = 0; i < n; i++) {
      string curr = q.front();
      q.pop();
      if (validStr(curr)) {
        foundFirstValid = true;
        result.push_back(curr);
      }
      
      for (size_t j = 0; !foundFirstValid && j < curr.size(); j++) {
        string child = curr;
        child.erase(j, 1);
        if (lookup.find(child) == lookup.end()) {
          q.push(child);
          lookup.insert(child);
        }
      }
    }
  }
  return result;
}

