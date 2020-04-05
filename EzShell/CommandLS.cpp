#include "CommandLS.h"
#include <iostream>
#include <dirent.h>
#include <fstream>
#include <algorithm>
#include <pwd.h>
#include <grp.h>
#include "CommandMAN.h"
using namespace std;

CommandLS::CommandLS(string str, DirHelper *dirHelper) : CommandBase(str, dirHelper) {

}

CommandLS::~CommandLS() {
    contents.clear();
}

bool CommandLS::cmpByName(const DirFile &A, const DirFile &B) {
    return A.name < B.name;
}

bool CommandLS::cmpByNameR(const DirFile &A, const DirFile &B) {
    return A.name > B.name;
}

bool CommandLS::cmpByTime(const DirFile &A, const DirFile &B) {
    return A.status.st_mtim.tv_sec > B.status.st_mtim.tv_sec;
}

bool CommandLS::cmpByTimeR(const DirFile &A, const DirFile &B) {
    return A.status.st_mtim.tv_sec < B.status.st_mtim.tv_sec;
}

void CommandLS::getInfo(string str) {
    Content cur(str);
    DIR *dir = opendir((dirHelper->getPath()+"/"+str).c_str());
    if (dir == NULL) {
        ifstream file(dirHelper->getPath()+"/"+str);
        if (file) {
            cur.type = 1;
        } else {
            cur.failed = 1;
        }
    } else {
        dirent *file;
        while (file = readdir(dir)) {
            DirFile df = DirFile(file->d_name);
            df.type = file->d_type;
            stat((dirHelper->getPath()+"/"+str+"/"+file->d_name).c_str(), &df.status);
            cur.file.push_back(df);
        }
        closedir(dir);
    }
    contents.push_back(cur);
}

void CommandLS::print(DirFile file) {
    if (file.name[0] == '.') {
        if (!_a && !_A) return;
        if (file.name == "." || file.name == "..") {
            if (!_a) return;
        }
    }
    if (_l) {
        if (S_ISDIR(file.status.st_mode)) cout << "d";
        else if (S_ISLNK(file.status.st_mode)) cout << "l";
        else if (S_ISBLK(file.status.st_mode)) cout << "b";
        else if (S_ISCHR(file.status.st_mode)) cout << "c";
        else if (S_ISFIFO(file.status.st_mode)) cout << "p";
        else if (S_ISSOCK(file.status.st_mode)) cout << "s";
        else cout << "-";
        if (file.status.st_mode & S_IRUSR) cout << "r";
        else cout << "-";
        if (file.status.st_mode & S_IWUSR) cout << "w";
        else cout << "-";
        if (file.status.st_mode & S_IXUSR) cout << "x";
        else cout << "-";
        if (file.status.st_mode & S_IRGRP) cout << "r";
        else cout << "-";
        if (file.status.st_mode & S_IWGRP) cout << "w";
        else cout << "-";
        if (file.status.st_mode & S_IXGRP) cout << "x";
        else cout << "-";
        if (file.status.st_mode & S_IROTH) cout << "r";
        else cout << "-";
        if (file.status.st_mode & S_IWOTH) cout << "w";
        else cout << "-";
        if (file.status.st_mode & S_IXOTH) cout << "x";
        else cout << "-";
        cout << " ";
        cout << file.status.st_nlink << " ";
        cout << getpwuid(file.status.st_uid)->pw_name << " ";
        cout << getgrgid(file.status.st_gid)->gr_name << " ";
        cout << file.status.st_size << " ";
        tm *tim = localtime(&file.status.st_mtim.tv_sec);
        cout << tim->tm_mon << " " << tim->tm_mday << " " << tim->tm_hour << ":" << tim->tm_min << " ";
    }
    if (file.type == DT_DIR) cout << "\033[1m\033[34m" << file.name << "\033[0m";
    else cout << file.name;
    if (_l) cout << endl;
    else cout << " ";
}

void CommandLS::show() {
    sort(contents.begin(), contents.end());
    if (contents.size() == 1) {
        if (contents[0].failed) {
            cout << "ls: cannot access \'" << contents[0].name << "\': No such file or directory" << endl;
        } else {
            if (_t) {
                if (_r) sort(contents[0].file.begin(), contents[0].file.end(), cmpByTimeR);
                else sort(contents[0].file.begin(), contents[0].file.end(), cmpByTime);
            } else {
                if (_r) sort(contents[0].file.begin(), contents[0].file.end(), cmpByNameR);
                else sort(contents[0].file.begin(), contents[0].file.end(), cmpByName);
            }
            for (int i = 0; i < contents[0].file.size(); ++i) {
                print(contents[0].file[i]);
            }
            cout << endl;
        }
    } else for (int i = 0; i < contents.size(); ++i) {
        if (contents[i].failed) {
            cout << "ls: cannot access \'" << contents[i].name << "\': No such file or directory" << endl;
        } else {
            if (_t) {
                if (_r) sort(contents[i].file.begin(), contents[i].file.end(), cmpByTimeR);
                else sort(contents[i].file.begin(), contents[i].file.end(), cmpByTime);
            } else {
                if (_r) sort(contents[i].file.begin(), contents[i].file.end(), cmpByNameR);
                else sort(contents[i].file.begin(), contents[i].file.end(), cmpByName);
            }
            for (int j = 0; j < contents[i].file.size(); ++j) {
                print(contents[i].file[j]);
            }
            cout << endl;
        }
    }
}

void CommandLS::run() {
    _a = _A = _l = _t = _r = false;
    for (int i = 0; i < opt.size(); ++i) {
        if (opt[i] == "-a") {
            _a = true;
        } else if (opt[i] == "-A") {
            _A = true;
        } else if (opt[i] == "-l") {
            _l = true;
        } else if (opt[i] == "-t") {
            _t = true;
        } else if (opt[i] == "-r") {
            _r = true;
        } else if (opt[i] == "--help") {
            CommandMAN *man = new CommandMAN("man ls", dirHelper);
            man->run();
            return;
        } else {
            cout << "ls: unrecognized option \'" << opt[i] << "\'" << endl;
            cout << "Try \'ls --help\' for more information" << endl;
            return;
        }
    }
    contents.clear();
    if (files.empty()) {
        getInfo(".");
    } else for (int i = 0; i < files.size(); ++i) {
        getInfo(files[i]);
    }
    show();
}