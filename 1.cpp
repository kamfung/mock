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

using namespace std;


bool isAbbriv(const string& s1, const string& s2){
  int idx1 = 0, idx2 = 0;
  
  while (idx2 < s2.size()) {
    if (isalpha(s2[idx2])) {
      if (idx1 >= s1.size() || s1[idx1] != s2[idx2]) {
        return false;
      }
      idx1++; idx2++;
    } else {
      int start = idx2;
      int num = 0;
      while (idx2 < s2.size() && !isalpha(s2[idx2])) {
        num = num * 10 + (s2[idx2++] - '0');
      }
      
      idx1 += num;
      if (idx1 >= s1.size()) {
        return false;
      }
    }
  }
  return (idx1 == s1.size());
} 

struct ListNode {
  int val;
  ListNode * next;
  ListNode (int x) { val = x; next = nullptr;}
};

int findLength(ListNode* h) {
  int res = 0;
  while (h != nullptr) {
    res ++;
    h = h -> next;
  }
  return res;
}

ListNode * findCommon(ListNode * head1, ListNode * head2)
{
  int len1 = findLength(head1);
  int len2 = findLength(head2);
  
  ListNode * & h1 = (len1 >= len2 ? head1 : head2);
  ListNode * & h2 = (len1 >= len2 ? head2 : head1);
  
  int diff = max(len1, len2) - min(len1, len2);
  
  for (int i = 0; i < diff; i ++) {
    h1 = h1 ->next;
  }
  
  while ( h1 != nullptr && h2 != nullptr) {
    if (h1 == h2) {
      return h1;
    } else {
      h1 = h1 ->next;
      h2 = h2 ->next;
    }
  }  
  return nullptr;
}

/*


result = "   "
input = "234"
currIdx = 0

findResult(input, currIdx, resultStr, result)

  if (currIdx == input.size()) {
    result.push_back(resultStr)
    return
  }
     

  for c in getMap(input[currIdx]) {
    result[currIdx] = c
    
    findResult(input, currIdx + 1, result)
  }


*/


string& digitToChars(char digit) {
    static unordered_map<char, string> lookup{{'2', "abc"}, 
                                              {'3', "def"},
                                              {'4', "ghi"},
                                              {'5', "jkl"},
                                              {'6', "mno"},
                                              {'7', "pqrs"},
                                              {'8', "tuv"},
                                              {'8', "wxyz"}};
  return lookup[digit];
}

void phoneNumToStringsHelper(const string&   phone, 
                             int             currIdx, 
                             string&         resSoFar, 
                             vector<string>& res) {
  // if (!dics.wordHasPref(resSoFar))
  if (currIdx == phone.size()) {
    res.push_back(resSoFar);
    return;
  }

  string& chars = digitToChars(phone[currIdx]);
  for (char c : chars) {
    resSoFar[currIdx] = c;
    phoneNumToStringsHelper(phone, currIdx + 1, resSoFar, res);
  }
}

vector<string> phoneNumToStrings(const string& phone) {
  vector<string> result;
  string         resSoFar(phone.size(), ' ');

  if (phone.empty()) {
    return result;
  }
  
  phoneNumToStringsHelper(phone, 0, resSoFar, result);
  return result;
}

/**

babad  => aba 
dp[0][0] for 'b' is true
dp[1][1] for 'a' is true
dp[2][2] for 'b' is true;
...
dp[0][1] 'ba' false
dp[1][2]  'ab' false
dp[2][3] 'ba', false
...

dp[0][2]. 'bab' check dp[1][1] ia true.

**/

/*auto
dp[i][j] = true when str[i:j] is palindromic
         = false otherwise
dp[i][j] = if cp is true and str[i] = str[j], true,
           false otherwise
*/

string longestPalin(const string &str) 
{
  int len = str.length();
  if (len == 0) {
    return str;
  }
  vector<vector<bool>> dp(len, vector<bool>(len, true));
  int maxlen = 0;
  string res;
  
  for (int size = 2; size <= len; size ++ ) { //size is the length of the substr
    for (int i = 0; i < len ; i ++ ) {
      int j = i + size - 1;
      if (j >= len) continue;
      //check if dp[i][j] of length size is palindromic
      if (str[i] != str[j] || (size > 2 && !dp[i + 1][j -1])) {
        dp[i][j] = false;
      }
      if (dp[i][j] && size > maxlen) {
        
        maxlen = size;
        res = str.substr(i, size);
        //cout << res << endl;
      }
    }
  }
  return res;
}

string expand (const string &str, int left, int right)
{  
    while (left >= 0  && right < str.length() && str[left] == str[right] ){
      left --;
      right ++;
    }
    return str.substr(left + 1, right - left - 1 );
}
    
string longestPalin2(const string &str) {
  int len = str.length();
  if (len == 0) {
    return str;
  }
  int maxlen = 0;
  string res;
  for(int i = 0; i < len; i ++) {
    string p1 = expand (str, i - 1, i + 1);
    string p2 = expand (str, i, i + 1);
    for (const string & p : { p1, p2}) {
      if (p.length() > maxlen) {
        maxlen = p.length();
        res = p;
      }
    }
  }
  return res;
}


//"aabacdb" return 2, return 
// 
// aabcdba
// 
// 
int indexOfFirstUniqueChar(const string& str) {
  unordered_map<char, int> lookup;
  
  for (char c : str) {
    lookup[c]++;
  }
  for (int i = 0 ; i < str.size(); ++i) {
    if (lookup[str[i]] == 1) {
      return i;
    }
  }
  return -1;
}

struct TCharMark {
  list<int>::iterator node;
  bool seenTwice = false;
  
};

// LRU
int indexOfFirstUniqueChar2(const string& str) {
  list<int> ls;
  unordered_map<char, TCharMark> lookup;
  
  for (int i = 0 ; i < str.size(); ++i) {
    if (lookup.find(str[i]) != lookup.end()) {
      if (!lookup[str[i]].seenTwice) {
        lookup[str[i]].seenTwice = true;
        ls.erase(lookup[str[i]].node);
      }
    } else {
      ls.push_back(i);
      lookup[str[i]].seenTwice = false;
      lookup[str[i]].node = prev(ls.end());
    }
  }
  
  return (ls.empty() ? -1 : ls.front());
}

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int v) {val = v; left = nullptr; right = nullptr;}
};

vector<vector<int>> levelTraversal(TreeNode * root)
{
  vector<vector<int>> res;
  queue<TreeNode*> q;
  
  if (root == nullptr) {
    return res;
  }
  q.push(root);
  
  while (!q.empty()) {
    int n = q.size();
    vector<int> v;
    for (int i = 0; i < n; i ++) {
      TreeNode * p = q.front();
      q.pop();
      v.push_back(p->val);
      if (p->left != nullptr) {
        q.push(p->left);
      }
      if (p->right != nullptr) {
        q.push(p->right);
      }
    }
    res.push_back(v);
  }  
  return res;
}

void helper(TreeNode* root, vector<vector<int>> & res, int level) {
  if (root == nullptr) {
    return;
  }
  if (res.size() <= level) {
    res.push_back(vector<int>());
  }
  res[level].push_back(root->val);
  helper(root->left, res, level + 1);
  helper(root->right, res, level + 1);
}

vector<vector<int>> levelbfs(TreeNode * root)
{
  vector<vector<int>> res;
  helper(root, res, 0);
  return res;
}


int main() {
  TreeNode root(3);
  root.left = new TreeNode(9);
  root.right = new TreeNode(2);
  root.left->left = new TreeNode(7);
  root.left->right = new TreeNode(8);
  vector<vector<int>> res = levelbfs(&root);
  for (const auto &v: res) {
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, " ")); 
    cout << endl;
  }
  return 0;
}

