#include <iostream>
#include <string.h>

using namespace std;

const int MAX_LOPSV = 500;
const int MAX_LOPTC = 10000;

struct MonHoc
{
    string MAMH;
    string TENMH;
    int STCLT;
    int STCTH;
};

struct NodeMH
{
    MonHoc mh;
    NodeMH *left;
    NodeMH *right;
};
typedef NodeMH *TreeMH;

struct SinhVien
{
    string MASV;
    string HO;
    string TEN;
    string GIOITINH;
    string SODT;
    string EMAIL;
};

struct NodeSV
{
    SinhVien sv;
    NodeSV *next;
};
typedef NodeSV *PTRSV;

struct LopSV
{
    string MALOP;
    string TENLOP;
    PTRSV FirstSV = NULL;
};

struct DSLopSV
{
    int n = 0;
    LopSV nodes[MAX_LOPSV];
};

struct DangKy
{
    string MASV;
    float DIEM = 0;
};

struct NodeDK
{
    DangKy dk;
    NodeDK *next;
};
typedef NodeDK *PTRDK;

struct LopTC
{
    int MALOPTC;
    string MAMH;
    string NIENKHOA;
    int HOCKY;
    int NHOM;
    int MINSV;
    int MAXSV;
    bool HUYLOP = false;
    PTRDK DSDK = NULL;
};

struct DSLopTC
{
    int n = 0;
    LopTC *nodes[MAX_LOPTC];
};

string ChuanHoa_Chuoi(string &chuoi, int dodai)
{
    size_t start = 0;
    while (start < chuoi.length() && isspace(static_cast<unsigned char>(chuoi[start])))
    {
        ++start;
    }
    size_t end = chuoi.length();
    while (end > start && isspace(static_cast<unsigned char>(chuoi[end - 1])))
    {
        --end;
    }
    string ketqua = chuoi.substr(start, end - start);
    if ((int)ketqua.length() > dodai)
    {
        cout << "Do dai chuoi vuot qua " << dodai << " ky tu!\n";
        return chuoi;
    }
    return ketqua;
}

PTRSV SearchSV_MASV(PTRSV &FirstSV, string &msv)
{
    for (PTRSV p = FirstSV; p != NULL; p = p->next)
    {
        if (strcasecmp(p->sv.MASV.c_str(), msv.c_str()) == 0)
            return p;
    }
    return NULL;
}

SinhVien Nhap_SV(PTRSV &FirstSV, SinhVien &sv)
{
    while (SearchSV_MASV(FirstSV, sv.MASV) != NULL)
    {
        cout << "Ma sinh vien da ton tai! Nhap lai ma sinh vien: ";
        cin >> sv.MASV;
        sv.MASV = ChuanHoa_Chuoi(sv.MASV, 15);
    }
    cout << "Nhap ho: ";
    cin >> sv.HO;
    sv.HO = ChuanHoa_Chuoi(sv.HO, 50);
    cout << "Nhap ten: ";
    cin >> sv.TEN;
    sv.TEN = ChuanHoa_Chuoi(sv.TEN, 50);
    cout << "Nhap gioi tinh: ";
    cin >> sv.GIOITINH;
    sv.GIOITINH = ChuanHoa_Chuoi(sv.GIOITINH, 4);
    cout << "Nhap so dien thoai: ";
    cin >> sv.SODT;
    sv.SODT = ChuanHoa_Chuoi(sv.SODT, 10);
    cout << "Nhap email: ";
    cin >> sv.EMAIL;
    sv.EMAIL = ChuanHoa_Chuoi(sv.EMAIL, 50);
    cout << "Nhap thanh cong!\n";
    return sv;
}

void Nhap_DSSV(PTRSV &FirstSV)
{
    SinhVien sv;
    cout << "Nhap ma sinh vien (0 la dung nhap): ";
    while (true)
    {
        cin >> sv.MASV;
        if (sv.MASV == "0")
        {
            break;
        }
        sv.MASV = ChuanHoa_Chuoi(sv.MASV, 15);
        sv = Nhap_SV(FirstSV, sv);
        PTRSV p = new NodeSV;
        p->sv = sv;
        p->next = NULL;
        if (FirstSV == NULL)
        {
            FirstSV = p;
        }
        else
        {
            PTRSV q = FirstSV;
            while (q->next != NULL)
            {
                q = q->next;
            }
            q->next = p;
        }
        cout << "Nhap ma sinh vien (=0 dung nhap): ";
    }
}

void LietKe_DSSV(PTRSV &FirstSV)
{
    if (FirstSV == NULL)
    {
        cout << "Danh sach rong!\n";
        return;
    }
    cout << "DANH SACH SINH VIEN:\n";
    cout << "-------------------------------------------------------------\n";
    cout << "MaSV\tHo\tTen\tGioiTinh\tSoDT\tEmail\n";
    cout << "-------------------------------------------------------------\n";
    for (PTRSV p = FirstSV; p != NULL; p = p->next)
    {
        cout << p->sv.MASV << "\t"
             << p->sv.HO << "\t"
             << p->sv.TEN << "\t"
             << p->sv.GIOITINH << "\t"
             << p->sv.SODT << "\t"
             << p->sv.EMAIL << "\n";
    }
}

void Them_LopTC(DSLopTC &DSLTC)
{
    if (DSLTC.n >= MAX_LOPTC)
    {
        cout << "Danh sach lop tin chi da day!\n";
        return;
    }
    LopTC *ltc = new LopTC;
    cout << "Nhap ma mon hoc: ";
    cin >> ltc->MAMH;
    cout << "Nhap nien khoa: ";
    cin >> ltc->NIENKHOA;
    cout << "Nhap hoc ky: ";
    cin >> ltc->HOCKY;
    cout << "Nhap nhom: ";
    cin >> ltc->NHOM;
    cout << "Nhap so luong sinh vien toi thieu: ";
    cin >> ltc->MINSV;
    cout << "Nhap so luong sinh vien toi da: ";
    cin >> ltc->MAXSV;
    ltc->MALOPTC = DSLTC.n + 1;
    ltc->HUYLOP = false;
    ltc->DSDK = NULL;
    DSLTC.nodes[DSLTC.n] = ltc;
    DSLTC.n++;
    cout << "Them lop tin chi thanh cong!" << endl;
}

void LietKe_LopTC(DSLopTC &DSLTC)
{
    if (DSLTC.n == 0)
    {
        cout << "Danh sach lop tin chi rong!\n";
        return;
    }
    cout << "DANH SACH LOP TIN CHI:\n";
    cout << "-------------------------------------------------------------\n";
    cout << "MaLTC\tMaMH\tNienKhoa\tHocKy\tNhom\tMinSV\tMaxSV\tHuyLop\n";
    cout << "-------------------------------------------------------------\n";
    for (int i = 0; i < DSLTC.n; i++)
    {
        LopTC *ltc = DSLTC.nodes[i];
        cout << ltc->MALOPTC << "\t"
             << ltc->MAMH << "\t"
             << ltc->NIENKHOA << "\t"
             << ltc->HOCKY << "\t"
             << ltc->NHOM << "\t"
             << ltc->MINSV << "\t"
             << ltc->MAXSV << "\t"
             << (ltc->HUYLOP ? "Yes" : "No") << endl;
    }
}

int main()
{
    DSLopTC DSLTC;
    TreeMH DSMH = NULL;
    DSLopSV DSLSV;
    PTRSV FirstSV = NULL;
    bool check = true;
    while (check)
    {
        cout << "=== MENU ===\n";
        cout << "1. Them lop tin chi\n";
        cout << "2. Liet ke lop tin chi\n";
        cout << "3. Xoa lop tin chi\n";
        cout << "4. Hieu chinh lop tin chi\n";
        cout << "5. Nhap danh sach sinh vien\n";
        cout << "6. Liet ke danh sach sinh vien\n";
        cout << "0. Thoat\n";
        int choice;
        cout << "Nhap lua chon: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            Them_LopTC(DSLTC);
            break;
        case 2:
            LietKe_LopTC(DSLTC);
            break;
        case 3:
            //Xoa_LopTC(DSLTC);
            break;
        case 4:
            //HieuChinh_LopTC(DSLTC);
            break;
        case 5:
            Nhap_DSSV(FirstSV);
            break;
        case 6:
            LietKe_DSSV(FirstSV);
            break;
        case 0:
            check = false;
            break;
        default:
            cout << "Nhap sai! Nhap lai!\n";
            break;
        }
    }
}