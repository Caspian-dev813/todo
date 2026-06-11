#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct Task
{
    string content;
    bool done;
};

const string FILE_NAME = "tasks.txt";

void loadTasks(vector<Task>& tasks)
{
    ifstream fin(FILE_NAME);
    if (!fin) return;
    string line;
    bool status;
    while (getline(fin, line))
    {
        fin >> status;
        fin.ignore();
        tasks.push_back({line, status});
    }
    fin.close();
}

void saveTasks(const vector<Task>& tasks)
{
    ofstream fout(FILE_NAME);
    for (auto& t : tasks)
    {
        fout << t.content << endl << t.done << endl;
    }
    fout.close();
}

int main()
{
    vector<Task> tasks;
    loadTasks(tasks);

    int op, idx;
    string text;

    while (true)
    {
        cout << "\n===== 终端Todo清单 =====" << endl;
        cout << "1. 添加任务" << endl;
        cout << "2. 查看所有任务" << endl;
        cout << "3. 标记任务完成" << endl;
        cout << "4. 删除任务" << endl;
        cout << "0. 退出程序" << endl;
        cout << "请输入操作序号：";
        cin >> op;
        cin.ignore();

        if (op == 0)
        {
            saveTasks(tasks);
            cout << "数据已保存，已退出" << endl;
            break;
        }

        switch (op)
        {
            case 1:
                cout << "请输入任务内容：";
                getline(cin, text);
                tasks.push_back({text, false});
                saveTasks(tasks);
                cout << "添加成功！" << endl;
                break;
            case 2:
                cout << "\n当前任务列表：" << endl;
                if (tasks.empty())
                {
                    cout << "暂无任务" << endl;
                    break;
                }
                for (int i = 0; i < tasks.size(); i++)
                {
                    string status = tasks[i].done ? "[√] " : "[ ] ";
                    cout << i + 1 << ". " << status << tasks[i].content << endl;
                }
                break;
            case 3:
                cout << "输入要标记的任务编号：";
                cin >> idx;
                if (idx < 1 || idx > tasks.size())
                {
                    cout << "编号无效" << endl;
                    break;
                }
                tasks[idx - 1].done = true;
                saveTasks(tasks);
                cout << "标记完成！" << endl;
                break;
            case 4:
                cout << "输入要删除的任务编号：";
                cin >> idx;
                if (idx < 1 || idx > tasks.size())
                {
                    cout << "编号无效" << endl;
                    break;
                }
                tasks.erase(tasks.begin() + idx - 1);
                saveTasks(tasks);
                cout << "删除成功！" << endl;
                break;
            default:
                cout << "无效选项，请重新输入" << endl;
        }
    }
    return 0;
}