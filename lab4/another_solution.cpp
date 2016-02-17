//
// Created by Potemkin Andrey Vladimirovich on 14.02.16.
//

#include <vector>
#include <iostream>
#include <string>

using namespace std;

class field {
  int m_;
  int n_;
  bool reversed_;
  bool solution_;
  vector<vector<char>> matrix_;//field contains hubs and connections
  enum direction {
    down,
    up,
  };

  char GetHub(int aY, int aX) {
    if(aY >= 0 && aX >= 0 && aY < n_ && aX < m_) {
      return matrix_[2 * aY][2 * aX];
    }
    return 0;
  }

  void SetHub(int aY, int aX, int aOldY = -1, int aOldX = -1) {
    if(aY >= 0 && aX >= 0 && aY < n_ && aX < m_) {
      matrix_[2 * aY][2 * aX] = 'o'; // here set hub
      //set connection, will bug if the start and end point are the same
      if(aOldX >= 0 && aOldX < m_ && aOldY >= 0 && aOldY < n_) {
        int dx = aY - aOldY;
        int dy = aX - aOldX;
        char dir = '-';
        if ((dx > 0 && dy > 0) || (dx < 0 && dy < 0)){
          dir = '\\';
        }
        if ((dx < 0 && dy > 0) || (dx > 0 && dy < 0)){
          dir = '/';
        }
        if (dx && !dy) {
          dir = '|';
        }
        if (dy && !dx) {
          dir = '-';
        }
        matrix_[ dx + aOldY * 2 ][dy + aOldX * 2 ] = dir;
      }
    }
    return;
  }
public:
  field(int aM, int aN){
    m_ = aM;
    n_ = aN;
    solution_ = false;
    reversed_ = false;
    Solve();
  }

  bool Solve(){
    // when field is 2-by-2
    if(m_ == 2 && n_ == 2){
      matrix_ = vector<vector<char>> (2 * n_ - 1,vector<char> (2 * m_ - 1,' '));
      SetHub(0, 0);
      SetHub(0, 1, 0, 0);
      SetHub(1, 1, 0, 1);
      SetHub(1, 0, 1, 1);
      SetHub(0, 0, 1, 0);
      solution_ = true;
      return true;
    }
    // field less or equal than 3 => no solution
    if((m_ % 2 != 0 && n_ % 2 != 0) || (m_ <= 3 || n_ <= 3) ) {
      solution_ = false;
      return false;
    }
    if(m_ % 4 > 1 && n_ % 4 > 1) {
      solution_ = false;
      return false;
    }
    int parity = 0; // pairity for 3 instead 2 by 2 subfields
    if( m_ % 4 == 0){
      matrix_ = vector<vector<char>> (2 * n_ - 1,vector<char> (2 * m_ - 1,' '));
      parity = 1;
    } else {
      // find solution with rotated matrix, anyway doesn't matter how to print
      if (m_ % 2 != 0) {
        matrix_ = vector<vector<char>> (2 * n_ - 1,vector<char> (2 * m_ - 1,' '));
      } else {
        swap(n_, m_);
        reversed_ = true;
        matrix_ = vector<vector<char>>(2 * n_ - 1, vector<char>(2 * m_ - 1, ' '));
      }
    }
    // start positions for this algo only 1 and 0...
    int start_y = 1;
    int start_x = 0;
    SetHub(start_y, start_x);
    int y = 2;
    int x = 1;
    SetHub(y, x, start_y, start_x);
    direction current_directon = up;
    char last_directon = '|';
    int pos = -1;
    int count = (n_ - 2) * 2;
    int right = 0,left = 0,top = 1, bottom = n_;
    //main part of field (except top 2 by n_)
    while (pos < m_ / 2 + 1) {
      if(count >= (n_ - (top + 1)) * (right - left)) {
        pos ++;
        right = 2 * (pos + 1) + !parity;
        left = 2 * pos + !parity;
        if(!parity && pos == 0){
          right = 3;
          left = 0;
        }
        top = 1;
        bottom = n_;
        count = 0;
        if(right > m_) {
          break;
        }
        if(current_directon == up) {
          current_directon = down;
        } else {
          current_directon = up;
        }
      }
      count ++;
      int old_y = y;
      int old_x = x;
      // priority of directons /\|- are very important
      if (current_directon == up) {
        if (y + 1 < bottom && last_directon != '|' && GetHub(y + 1, x) != 'o') {
          last_directon = '|';
          y++;
        } else if (y + 1 < bottom && x - 1 >= left && last_directon != '/' && GetHub(y + 1, x - 1) != 'o') {
          last_directon = '/';
          y++;
          x--;
        } else if (x + 1 < right && y + 1 < bottom && last_directon != '\\' && GetHub(y + 1, x + 1) != 'o') {
          last_directon = '\\';
          y++;
          x++;
        } else if (x - 1 >= left && last_directon != '-' && GetHub(y, x - 1) != 'o') {
          last_directon = '-';
          x--;
        } else if (x + 1 < right && last_directon != '-' && GetHub(y, x + 1) != 'o') {
          last_directon = '-';
          x++;
        } else if (x - 1 >= left && last_directon != '\\' && y - 1 > top && GetHub(y - 1, x - 1) != 'o') {
          last_directon = '\\';
          y--;
          x--;
        } else if (y - 1 > top && last_directon != '|' && GetHub(y - 1, x) != 'o') {
          last_directon = '|';
          y--;
        } else if (x + 1 < right && last_directon != '/' && y - 1 > top && GetHub(y - 1, x + 1) != 'o') {
          last_directon = '/';
          y--;
          x++;
        }
      } else if (current_directon == down) {
        if (y - 1 > top && last_directon != '|' && GetHub(y - 1, x) != 'o') {
          last_directon = '|';
          y--;
        } else if (y - 1 > top && x - 1 >= left && last_directon != '\\' && GetHub(y - 1, x - 1) != 'o') {
          last_directon = '\\';
          y--;
          x--;
        } else if (x + 1 < right && y - 1 > top && last_directon != '/' && GetHub(y - 1, x + 1) != 'o') {
          last_directon = '/';
          y--;
          x++;
        } else if (x - 1 >= left && last_directon != '-' && GetHub(y, x - 1) != 'o') {
          last_directon = '-';
          x--;
        } else if (x + 1 < right && last_directon != '-' && GetHub(y, x + 1) != 'o') {
          last_directon = '-';
          x++;
        } else if (x - 1 >= left && last_directon != '/' && y + 1 < bottom && GetHub(y + 1, x - 1) != 'o') {
          last_directon = '/';
          y++;
          x--;
        } else if (y + 1 < bottom && last_directon != '|' && GetHub(y + 1, x) != 'o') {
          last_directon = '|';
          y++;
        } else if (x + 1 < right && last_directon != '\\' && y + 1 < bottom && GetHub(y + 1, x + 1) != 'o') {
          last_directon = '\\';
          y++;
          x++;
        }
      }
      // setting up hub on field
      if(!(y==old_y && x==old_x) ) {
        SetHub(y, x, old_y, old_x);
      }
    }
    //handle transition to top part
    right = m_;
    left = 0;
    top = -1;
    bottom = 2;
    //
    int old_x = x,
        old_y = y;
    if (y - 1 > top && x - 1 >= left && last_directon != '\\' && GetHub(y - 1, x - 1) != 'o') {
      last_directon = '\\';
      y--;
      x--;
    } else if (x + 1 < right && y - 1 > top && last_directon != '/' && GetHub(y - 1, x + 1) != 'o') {
      last_directon = '/';
      y--;
      x++;
    } else if (x - 1 >= left && last_directon != '-' && GetHub(y, x - 1) != 'o') {
      last_directon = '-';
      x--;
    } else if (x + 1 < right && last_directon != '-' && GetHub(y, x + 1) != 'o') {
      last_directon = '-';
      x++;
    } else if (x - 1 >= left && last_directon != '/' && y + 1 < bottom && GetHub(y + 1, x - 1) != 'o') {
      last_directon = '/';
      y++;
      x--;
    } else if (y + 1 < bottom && last_directon != '|' && GetHub(y + 1, x) != 'o') {
      last_directon = '|';
      y++;
    } else if (y - 1 > top && last_directon != '|' && GetHub(y - 1, x) != 'o') {
      last_directon = '|';
      y--;
    } else if (x + 1 < right && last_directon != '\\' && y + 1 < bottom && GetHub(y + 1, x + 1) != 'o') {
      last_directon = '\\';
      y++;
      x++;
    }
    if(!(y==old_y && x==old_x) ) {
      SetHub(y, x, old_y, old_x);
    }
    count = 0;
    // handle top
    while(x > 0 && count < 2 * m_) {
      int old_x = x;
      int old_y = y;
      if (x + 1 < right && last_directon != '-' && GetHub(y, x + 1) != 'o') {
        last_directon = '-';
        x++;
      } else if (x + 1 < right && last_directon != '\\' && y + 1 < bottom && GetHub(y + 1, x + 1) != 'o') {
        last_directon = '\\';
        y++;
        x++;
      } else if (x + 1 < right && y - 1 > top && last_directon != '/' && GetHub(y - 1, x + 1) != 'o') {
        last_directon = '/';
        y--;
        x++;
      } else if (y - 1 > top && last_directon != '|' && GetHub(y - 1, x) != 'o') {
        last_directon = '|';
        y--;
      } else if (y + 1 < bottom && last_directon != '|' && GetHub(y + 1, x) != 'o') {
        last_directon = '|';
        y++;
      } else if (y - 1 > top && x - 1 >= left && last_directon != '\\' && GetHub(y - 1, x - 1) != 'o') {
        last_directon = '\\';
        y--;
        x--;
      } else if (x - 1 >= left && last_directon != '/' && y + 1 < bottom && GetHub(y + 1, x - 1) != 'o') {
        last_directon = '/';
        y++;
        x--;
      } else if (x - 1 >= left && last_directon != '-' && GetHub(y, x - 1) != 'o') {
        last_directon = '-';
        x--;
      }
      if(!(y==old_y && x==old_x) ) {
        SetHub(y, x, old_y, old_x);
      }
      count++;
    }
    SetHub(start_y,start_x,y,x);
    solution_ = true;
    return true;
  }

  void print() {
    if(solution_) {
      cout << "Yes" << endl;
      if(!reversed_) {
        for (int i = 0; i < matrix_.size(); i++) {
          for (int j = 0; j < matrix_[i].size(); j++) {
            cout << matrix_[i][j];
          }
          cout << endl;
        }
      } else {
        for (int i = 0; i < matrix_[0].size(); i++) {
          for (int j = 0; j < matrix_.size(); j++) {
            if(matrix_[j][i] == '-') {
              cout << '|';
            } else if(matrix_[j][i] == '|') {
              cout <<  '-';
            } else if(matrix_[j][i] == '/') {
              cout << '/';
            } else if(matrix_[j][i] == '\\') {
              cout << '\\';
            } else {
              cout << matrix_[j][i];
            }
          }
          cout << endl;
        }
      }
    } else {
      cout << "No";
    }
  }
};

int main() {
  int N,M;
  cin >> N >> M;
  field sol(M,N);
  sol.print();
  return 0;
}
