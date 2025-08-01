#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <conio.h>

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
    int SLSV = 0;
    PTRSV FirstSV = NULL;
};

void Xoa_SV_LopSV(PTRSV &FirstSV);

struct DSLopSV
{
    int n = 0;
    int capacity = 100;
    LopSV *nodes;
    DSLopSV();
    ~DSLopSV();
};

DSLopSV::DSLopSV()
{
    nodes = new LopSV[capacity];
}

DSLopSV::~DSLopSV()
{
    for (int i = 0; i < n; i++)
    {
        Xoa_SV_LopSV(nodes[i].FirstSV);
    }
    delete[] nodes;
}

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
    int SLSVDK = 0;
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

string ChuanHoa_InputNangCao(string chuoi, int dodai, bool toUpper = false, bool vietHoaDau = false)
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
    string tam = chuoi.substr(start, end - start);
    string hopLe = "";
    for (char c : tam)
    {
        if (isalnum(c) || c == '-' || c == '_' || isspace(static_cast<unsigned char>(c)))
            hopLe += c;
    }
    stringstream ss(hopLe);
    string word, ketqua;
    while (ss >> word)
    {
        if (!ketqua.empty())
            ketqua += " ";
        ketqua += word;
    }
    if (toUpper)
    {
        for (char &c : ketqua)
            c = toupper(c);
    }
    if (vietHoaDau) {
    bool capitalize = true;
    for (char &c : ketqua)
	{
        if (isspace(c)) {
            capitalize = true;
        } else if (capitalize && isalpha(c)) {
            c = toupper(c);
            capitalize = false;
        } else {
            c = tolower(c);
        }
    }
}
    return ChuanHoa_Chuoi(ketqua, dodai);
}

bool KiemTra_SDT(string sdt)
{
    if (sdt.length() != 10)
        return false;
    for (char c : sdt)
        if (!isdigit(c))
            return false;
    return true;
}

bool KiemTra_Email(string email)
{
    size_t at = email.find('@');
    size_t dot = email.find('.', at);
    return at != string::npos && dot != string::npos && dot > at;
}

// bool KiemTra_TrungMaSV(PTRSV FirstSV, string masv)
// {
//     for (PTRSV p = FirstSV; p != NULL; p = p->next)
//         if (strcasecmp(p->sv.MASV.c_str(), masv.c_str()) == 0)
//             return true;
//     return false;
// }
bool KiemTra_ChuaChuVaSo(string s) {
    bool coChu = false, coSo = false;
    for (char c : s) {
        if (isalpha(c)) coChu = true;
        if (isdigit(c)) coSo = true;
    }
    return coChu && coSo;
}

bool isNumber(string s) {
    for (char c : s)
        if (!isdigit(c)) return false;
    return !s.empty();
}
/*Tiến*/
PTRSV SearchSV_MASV(DSLopSV &DSLSV, string msv)
{
    for (int i = 0; i < DSLSV.n; i++)
    {
        PTRSV p = DSLSV.nodes[i].FirstSV;
        while (p != NULL)
        {
            if (strcasecmp(p->sv.MASV.c_str(), msv.c_str()) == 0)
            {
                return p;
            }
            p = p->next;
        }
    }
    return NULL;
}

void LietKe_DSSV(DSLopSV &DSLSV)
{
    cout << "--- DANH SACH SINH VIEN ---\n";
    cout << "------------------------------------------------------------------------------\n";
    cout << "MaSV\t\tHo\t\tTen\tGioiTinh\tSoDT\t\tEmail\n";
    cout << "------------------------------------------------------------------------------\n";
    for (int i = 0; i < DSLSV.n; i++)
    {
        for (PTRSV p = DSLSV.nodes[i].FirstSV; p != NULL; p = p->next)
        {
            cout << p->sv.MASV << "\t"
                 << p->sv.HO << "\t"
                 << p->sv.TEN << "\t"
                 << p->sv.GIOITINH << "\t\t"
                 << p->sv.SODT << "\t"
                 << p->sv.EMAIL << "\n";
        }
    }
}

string SearchTenMH_MAMH(TreeMH &DSMH, string mamh)
{
    if (DSMH == NULL)
    {
        return "";
    }
    if (strcasecmp(DSMH->mh.MAMH.c_str(), mamh.c_str()) == 0)
    {
        return DSMH->mh.TENMH;
    }
    if (mamh < DSMH->mh.MAMH)
    {
        return SearchTenMH_MAMH(DSMH->left, mamh);
    }
    if (mamh > DSMH->mh.MAMH)
    {
        return SearchTenMH_MAMH(DSMH->right, mamh);
    }
}

void Them_LopTC(DSLopTC &DSLTC, TreeMH &DSMH)
{
    if (DSLTC.n >= MAX_LOPTC)
    {
        cout << "Danh sach lop tin chi da day!\n";
        return;
    }
    LopTC *ltc = new LopTC;
    cout << "Nhap ma mon hoc: ";
    cin >> ltc->MAMH;
    cout << "Ten mon hoc: " << SearchTenMH_MAMH(DSMH, ltc->MAMH) << "\n";
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
    cout << "Them lop tin chi thanh cong!\n";
}

LopTC *SearchLopTC_MALTC(DSLopTC &DSLTC)
{
    if (DSLTC.n == 0)
    {
        return NULL;
    }
    int mltc;
    cout << "Nhap ma lop tin chi: ";
    cin >> mltc;
    LopTC *p;
    for (int i = 0; i < DSLTC.n; i++)
    {
        p = DSLTC.nodes[i];
        if (p->MALOPTC == mltc)
            return p;
    }
    return NULL;
}

void HieuChinh_LopTC(DSLopTC &DSLTC)
{
    LopTC *ltc = SearchLopTC_MALTC(DSLTC);
    if (ltc == NULL)
    {
        cout << "Khong tim thay lop tin chi!\n";
        return;
    }
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
    cout << "Nhap huy lop (Y/N): ";
    string huylop;
    cin >> huylop;
    if (strcasecmp(huylop.c_str(), "Y") == 0)
        ltc->HUYLOP = true;
    else
        ltc->HUYLOP = false;
    cout << "Hieu chinh lop tin chi thanh cong!\n";
}

void Xoa_LopTC(DSLopTC &DSLTC)
{
    LopTC *ltc = SearchLopTC_MALTC(DSLTC);
    if (ltc == NULL)
    {
        cout << "Khong tim thay lop tin chi!\n";
        return;
    }
    cout << "Ban co chac chan muon xoa? (Y/N): ";
    string xacnhan;
    cin >> xacnhan;
    if (strcasecmp(xacnhan.c_str(), "Y") != 0)
    {
        cout << "Da huy thao tac xoa!\n";
        return;
    }
    int vitri = -1;
    for (int i = 0; i < DSLTC.n; i++)
    {
        if (DSLTC.nodes[i] == ltc)
        {
            vitri = i;
            break;
        }
    }
    if (vitri == -1)
    {
        cout << "Lop tin chi khong ton tai!\n";
        return;
    }
    delete DSLTC.nodes[vitri];
    for (int i = vitri; i < DSLTC.n - 1; i++)
    {
        DSLTC.nodes[i] = DSLTC.nodes[i + 1];
    }
    DSLTC.n--;
    cout << "Da xoa lop tin chi co ma " << ltc->MALOPTC << " thanh cong!\n";
}

void LietKe_LopTC(DSLopTC &DSLTC, TreeMH &DSMH)
{
    string nienkhoa;
    cout << "Nhap nien khoa: ";
    cin >> nienkhoa;
    int hocky;
    cout << "Nhap hoc ky: ";
    cin >> hocky;
    cout << "--- DANH SACH LOP TIN CHI - Nien Khoa: " << nienkhoa << ", Hoc Ky: " << hocky << " ---\n";
    cout << "------------------------------------------------------------------------------------------------------------------\n";
    cout << left
         << setw(8) << "MaLTC"
         << setw(10) << "MaMH"
         << setw(35) << "TenMH"
         << setw(12) << "NienKhoa"
         << setw(7) << "HocKy"
         << setw(6) << "Nhom"
         << setw(7) << "MinSV"
         << setw(7) << "MaxSV"
         << setw(16) << "SoLuongDK"
         << setw(8) << "HuyLop"
         << "\n";
    cout << "------------------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < DSLTC.n; i++)
    {
        LopTC *ltc = DSLTC.nodes[i];
        if (ltc->NIENKHOA == nienkhoa && ltc->HOCKY == hocky)
        {
            string tenmh = SearchTenMH_MAMH(DSMH, ltc->MAMH);
            cout << left
                 << setw(8) << ltc->MALOPTC
                 << setw(10) << ltc->MAMH
                 << setw(35) << tenmh
                 << setw(12) << ltc->NIENKHOA
                 << setw(7) << ltc->HOCKY
                 << setw(6) << ltc->NHOM
                 << setw(7) << ltc->MINSV
                 << setw(7) << ltc->MAXSV
                 << setw(16) << ltc->SLSVDK
                 << setw(8) << (ltc->HUYLOP ? "Yes" : "No")
                 << "\n";
        }
    }
}

LopTC *SearchLopTC(DSLopTC &DSLTC, string mamh, string nienkhoa, int hocky, int nhom)
{
    for (int i = 0; i < DSLTC.n; i++)
    {
        if (strcasecmp(DSLTC.nodes[i]->MAMH.c_str(), mamh.c_str()) == 0 && strcasecmp(DSLTC.nodes[i]->NIENKHOA.c_str(), nienkhoa.c_str()) == 0 && DSLTC.nodes[i]->HOCKY == hocky && DSLTC.nodes[i]->NHOM == nhom)
        {
            return DSLTC.nodes[i];
        }
    }
    return NULL;
}

void InDSSV_LopTC(DSLopTC &DSLTC, DSLopSV &DSLSV)
{
    string mamh, nienkhoa;
    int hocky, nhom;
    cout << "Nhap ma mon hoc: ";
    cin >> mamh;
    cout << "Nhap nien khoa: ";
    cin >> nienkhoa;
    cout << "Nhap hoc ky: ";
    cin >> hocky;
    cout << "Nhap nhom: ";
    cin >> nhom;
    LopTC *ltc = SearchLopTC(DSLTC, mamh, nienkhoa, hocky, nhom);
    if (ltc == NULL)
    {
        cout << "Khong ton tai lop tin chi nay!\n";
        return;
    }
    if (ltc->DSDK == NULL)
    {
        cout << "Danh sach sinh vien rong!\n";
        return;
    }
    cout << "--- DANH SACH SINH VIEN DANG KY LOP " << mamh << " - HOC KY " << hocky << " - NIEN KHOA " << nienkhoa << " - NHOM " << nhom << " ---\n";
    cout << "----------------------------------------------------------------------------------------------------\n";
    cout << "MaSV\t\tHo\t\tTen\t\tGioiTinh\tSo DT\t\tEmail\n";
    cout << "----------------------------------------------------------------------------------------------------\n";
    NodeDK *p = ltc->DSDK;
    while (p != NULL)
    {
        PTRSV node = SearchSV_MASV(DSLSV, p->dk.MASV);
        if (node != NULL)
        {
            cout << node->sv.MASV << "\t" << node->sv.HO << "\t" << node->sv.TEN << "\t\t" << node->sv.GIOITINH << "\t\t" << node->sv.SODT << "\t" << node->sv.EMAIL << "\n";
        }
        p = p->next;
    }
}

void DangKy_LopTC(DSLopTC &DSLTC, TreeMH &DSMH, DSLopSV &DSLSV)
{
    string masv;
    cout << "Nhap ma sinh vien: ";
    cin >> masv;
    PTRSV p = SearchSV_MASV(DSLSV, masv);
    if (p == NULL)
    {
        cout << "Khong tim thay sinh vien!\n";
        return;
    }
    else
    {
        cout << "Ma sinh vien: " << p->sv.MASV << "\n";
        cout << "Ho: " << p->sv.HO << "\n";
        cout << "Ten: " << p->sv.TEN << "\n";
        cout << "Gioi tinh: " << p->sv.GIOITINH << "\n";
        cout << "So dien thoai: " << p->sv.SODT << "\n";
        cout << "Email: " << p->sv.EMAIL << "\n";
    }
    string nienkhoa;
    cout << "Nhap nien khoa: ";
    cin >> nienkhoa;
    int hocky;
    cout << "Nhap hoc ky: ";
    cin >> hocky;
    cout << "DANH SACH LOP TIN CHI - NIEN KHOA " << nienkhoa << " - HOC KY " << hocky << "\n";
    cout << "-----------------------------------------------------------------------------\n";
    cout << left
         << setw(10) << "MaMH"
         << setw(35) << "TenMH"
         << setw(8) << "Nhom"
         << setw(15) << "So SV Da DK"
         << setw(10) << "Con Trong" << "\n";
    for (int i = 0; i < DSLTC.n; i++)
    {
        LopTC *ltc = DSLTC.nodes[i];
        if (strcasecmp(ltc->NIENKHOA.c_str(), nienkhoa.c_str()) == 0 && ltc->HOCKY == hocky && ltc->HUYLOP == false)
        {
            string tenmh = SearchTenMH_MAMH(DSMH, ltc->MAMH);
            cout << left
                 << setw(10) << ltc->MAMH
                 << setw(35) << tenmh
                 << setw(8) << ltc->NHOM
                 << setw(15) << ltc->SLSVDK
                 << setw(10) << (ltc->MAXSV - ltc->SLSVDK) << "\n";
        }
    }
    cout << "--- Nhap thong tin dang ky mon hoc ---\n";
    string mamh;
    cout << "Nhap ma mon hoc muon dang ky: ";
    cin >> mamh;
    int nhom;
    cout << "Nhap nhom muon dang ky: ";
    cin >> nhom;
    for (int i = 0; i < DSLTC.n; i++)
    {
        LopTC *ltc = DSLTC.nodes[i];
        if (strcasecmp(ltc->MAMH.c_str(), mamh.c_str()) == 0 && ltc->NHOM == nhom && strcasecmp(ltc->NIENKHOA.c_str(), nienkhoa.c_str()) == 0 && ltc->HOCKY == hocky && ltc->HUYLOP == false)
        {
            if (ltc->MAXSV - ltc->SLSVDK == 0)
            {
                cout << "So luong sv dang ky da day!\n";
                return;
            }
            else
            {
                ltc->SLSVDK++;
                PTRDK node = new NodeDK;
                node->dk.MASV = p->sv.MASV;
                node->next = NULL;
                if (ltc->DSDK == NULL)
                {
                    ltc->DSDK = node;
                }
                else
                {
                    NodeDK *temp = ltc->DSDK;
                    while (temp->next != NULL)
                    {
                        temp = temp->next;
                    }
                    temp->next = node;
                }
            }
        }
    }
}
/*Tiến*/

/*Tài*/
int Tim_LopSV(DSLopSV &DSLSV, string malop)
{
    for (int i = 0; i < DSLSV.n; i++)
    {
        if (strcasecmp(DSLSV.nodes[i].MALOP.c_str(), malop.c_str()) == 0)
            return i;
    }
    return -1;
}

void MoRong_DSLopSV(DSLopSV &DSLSV)
{
    int new_capacity = DSLSV.capacity * 2;
    if (new_capacity > MAX_LOPSV)
        new_capacity = MAX_LOPSV;
    LopSV *new_nodes = new LopSV[new_capacity];
    for (int i = 0; i < DSLSV.n; i++)
    {
        new_nodes[i] = DSLSV.nodes[i];
    }
    delete[] DSLSV.nodes;
    DSLSV.nodes = new_nodes;
    DSLSV.capacity = new_capacity;
    cout << "Da mo rong danh sach lop sinh vien! Kich thuoc moi: " << new_capacity << endl;
}

void Them_LopSV(DSLopSV &DSLSV)
{
    if (DSLSV.n >= MAX_LOPSV)
    {
        cout << "Da dat gioi han toi da " << MAX_LOPSV << " lop sinh vien!\n";
        return;
    }
    if (DSLSV.n >= DSLSV.capacity)
    {
        cout << "Mang da day! Dang mo rong...\n";
        MoRong_DSLopSV(DSLSV);
    }
    string malop, tenlop;
    cout << "Nhap ma lop: ";
    cin >> malop;
    malop = ChuanHoa_Chuoi(malop, 15);
    if (Tim_LopSV(DSLSV, malop) != -1)
    {
        cout << "Ma lop da ton tai!\n";
        return;
    }
    cout << "Nhap ten lop: ";
    cin.ignore(1000, '\n');
    getline(cin, tenlop);
    DSLSV.nodes[DSLSV.n].MALOP = malop;
    DSLSV.nodes[DSLSV.n].TENLOP = tenlop;
    DSLSV.nodes[DSLSV.n].FirstSV = NULL;
    DSLSV.n++;
    cout << "Them lop sinh vien thanh cong!\n";
    cout << "So luong lop hien tai: " << DSLSV.n << "/" << DSLSV.capacity << endl;
}

void Xoa_SV_LopSV(PTRSV &FirstSV)
{
    while (FirstSV != NULL)
    {
        PTRSV temp = FirstSV;
        FirstSV = FirstSV->next;
        delete temp;
    }
}

void Xoa_LopSV(DSLopSV &DSLSV)
{
    if (DSLSV.n == 0)
    {
        cout << "Danh sach lop sinh vien rong!\n";
        return;
    }
    string malop;
    cout << "Nhap ma lop can xoa: ";
    cin >> malop;
    malop = ChuanHoa_Chuoi(malop, 15);
    int pos = Tim_LopSV(DSLSV, malop);
    if (pos == -1)
    {
        cout << "Khong tim thay lop!\n";
        return;
    }
    Xoa_SV_LopSV(DSLSV.nodes[pos].FirstSV);
    for (int i = pos; i < DSLSV.n - 1; i++)
    {
        DSLSV.nodes[i] = DSLSV.nodes[i + 1];
    }
    DSLSV.n--;
    cout << "Xoa lop sinh vien thanh cong!\n";
}

void HieuChinh_LopSV(DSLopSV &DSLSV)
{
    if (DSLSV.n == 0)
    {
        cout << "Danh sach lop sinh vien rong!\n";
        return;
    }
    string malop;
    cout << "Nhap ma lop can hieu chinh: ";
    cin >> malop;
    malop = ChuanHoa_Chuoi(malop, 15);
    int pos = Tim_LopSV(DSLSV, malop);
    if (pos == -1)
    {
        cout << "Khong tim thay lop!\n";
        return;
    }
    cout << "Thong tin hien tai:\n";
    cout << "Ma lop: " << DSLSV.nodes[pos].MALOP << "\n";
    cout << "Ten lop: " << DSLSV.nodes[pos].TENLOP << "\n";
    cout << "Nhap ten lop moi: ";
    cin.ignore();
    getline(cin, DSLSV.nodes[pos].TENLOP);
    cout << "Hieu chinh thanh cong!\n";
}

bool KiemTra_SV(PTRSV FirstSV, string masv)
{
    for (PTRSV p = FirstSV; p != NULL; p = p->next)
    {
        if (p->sv.MASV == masv)
        {
            return true;
        }
    }
    return false;
}

void Nhap_DSSV_TheoMSSV(PTRSV &FirstSV, DSLopSV DSLSV)
{
    string masv;
    cout << "Nhap ma sinh vien (0 de dung nhap): ";
    while (true)
    {
        cin >> masv;

        if (masv == "0")
        {
            break;
        }

        masv = ChuanHoa_Chuoi(masv, 15);

        PTRSV svTim = SearchSV_MASV(DSLSV, masv);
        if (svTim == NULL)
        {
            cout << "Khong tim thay sinh vien co ma: " << masv << "\n";
            cout << "Nhap ma sinh vien (de trong de dung nhap): ";
            continue;
        }

        if (KiemTra_SV(FirstSV, masv))
        {
            cout << "Sinh vien da ton tai trong lop!\n";
            cout << "Nhap ma sinh vien (de trong de dung nhap): ";
            continue;
        }

        PTRSV p = new NodeSV;
        p->sv = svTim->sv;
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

        cout << "Da them sinh vien: " << svTim->sv.HO << " " << svTim->sv.TEN << "\n";
        cout << "Nhap ma sinh vien (de trong de dung nhap): ";
    }
}

void Nhap_SV_Lop(DSLopSV &DSLSV, PTRSV FirstSV)
{
    if (DSLSV.n == 0)
    {
        cout << "Danh sach lop sinh vien rong!\n";
        return;
    }

    if (FirstSV == NULL)
    {
        cout << "Danh sach sinh vien tong rong!\n";
        return;
    }

    string malop;
    cout << "Nhap ma lop: ";
    cin >> malop;
    malop = ChuanHoa_Chuoi(malop, 15);
    int pos = Tim_LopSV(DSLSV, malop);
    if (pos == -1)
    {
        cout << "Khong tim thay lop!\n";
        return;
    }
    cout << "Nhap sinh vien vao lop " << DSLSV.nodes[pos].TENLOP << ":\n";
    Nhap_DSSV_TheoMSSV(DSLSV.nodes[pos].FirstSV, DSLSV);
}

void LietKe_LopSV(DSLopSV &DSLSV)
{
    if (DSLSV.n == 0)
    {
        cout << "Danh sach lop sinh vien rong!\n";
        return;
    }
    cout << "DANH SACH LOP SINH VIEN:\n";
    cout << "-------------------------------------------------------------\n";
    cout << "STT\tMa Lop\t\tTen Lop\t\t\t\tSo SV\n";
    cout << "-------------------------------------------------------------\n";
    for (int i = 0; i < DSLSV.n; i++)
    {
        int count = 0;
        for (PTRSV p = DSLSV.nodes[i].FirstSV; p != NULL; p = p->next)
        {
            count++;
        }

        cout << (i + 1) << "\t"
             << DSLSV.nodes[i].MALOP << "\t\t"
             << DSLSV.nodes[i].TENLOP << "\t\t"
             << count << "\n";
    }
}

int SoSanh_Chuoi(const string &s1, const string &s2)
{
    int len1 = s1.length();
    int len2 = s2.length();
    int minLen = (len1 < len2) ? len1 : len2;
    for (int i = 0; i < minLen; i++)
    {
        char c1 = tolower(s1[i]);
        char c2 = tolower(s2[i]);
        if (c1 < c2)
            return -1;
        if (c1 > c2)
            return 1;
    }
    if (len1 < len2)
        return -1;
    if (len1 > len2)
        return 1;
    return 0;
}

bool SoSanh_TenHo(const SinhVien &sv1, const SinhVien &sv2)
{
    int result = SoSanh_Chuoi(sv1.TEN, sv2.TEN);
    if (result != 0)
        return result < 0;
    return SoSanh_Chuoi(sv1.HO, sv2.HO) < 0;
}

void SapXep_DSSV_TenHo(PTRSV &FirstSV)
{
    if (FirstSV == NULL || FirstSV->next == NULL)
        return;
    for (PTRSV i = FirstSV; i->next != NULL; i = i->next)
    {
        PTRSV min = i;
        for (PTRSV j = i->next; j != NULL; j = j->next)
        {
            if (SoSanh_TenHo(j->sv, min->sv))
            {
                min = j;
            }
        }
        if (min != i)
        {
            SinhVien temp = i->sv;
            i->sv = min->sv;
            min->sv = temp;
        }
    }
}

void In_DSSV_Lop_SapXep(DSLopSV &DSLSV)
{
    if (DSLSV.n == 0)
    {
        cout << "Danh sach lop sinh vien rong!\n";
        return;
    }
    string malop;
    cout << "Nhap ma lop: ";
    cin >> malop;
    malop = ChuanHoa_Chuoi(malop, 15);
    int pos = Tim_LopSV(DSLSV, malop);
    if (pos == -1)
    {
        cout << "Khong tim thay lop!\n";
        return;
    }
    if (DSLSV.nodes[pos].FirstSV == NULL)
    {
        cout << "Lop khong co sinh vien nao!\n";
        return;
    }
    SapXep_DSSV_TenHo(DSLSV.nodes[pos].FirstSV);
    cout << "--- DANH SACH SINH VIEN LOP " << DSLSV.nodes[pos].TENLOP << " (sap xep theo ten+ho) ---\n";
    cout << "-------------------------------------------------------------\n";
    cout << "STT\tMaSV\t\tHo\t\tTen\tGioiTinh\tSoDT\t\tEmail\n";
    cout << "-------------------------------------------------------------\n";
    int stt = 1;
    for (PTRSV p = DSLSV.nodes[pos].FirstSV; p != NULL; p = p->next)
    {
        cout << stt << "\t"
             << p->sv.MASV << "\t"
             << p->sv.HO << "\t"
             << p->sv.TEN << "\t"
             << p->sv.GIOITINH << "\t\t"
             << p->sv.SODT << "\t"
             << p->sv.EMAIL << "\n";
        stt++;
    }
}

void NhapDiem_LopTC(DSLopTC &DSLTC, TreeMH &DSMH, DSLopSV &DSLSV)
{
    string mamh, nienkhoa;
    int hocky, nhom;
    cout << "Nhap ma mon hoc: ";
    cin >> mamh;
    cout << "Nhap nien khoa: ";
    cin >> nienkhoa;
    cout << "Nhap hoc ky: ";
    cin >> hocky;
    cout << "Nhap nhom: ";
    cin >> nhom;
    LopTC *ltc = SearchLopTC(DSLTC, mamh, nienkhoa, hocky, nhom);
    if (ltc == NULL)
    {
        cout << "Khong ton tai lop tin chi nay!\n";
        return;
    }
    if (ltc->DSDK == NULL)
    {
        cout << "Lop tin chi chua co sinh vien dang ky!\n";
        return;
    }
    string tenmh = SearchTenMH_MAMH(DSMH, mamh);
    cout << "\nMon hoc: " << mamh << " - " << tenmh << "\n";
    cout << "Nien khoa: " << nienkhoa << " - Hoc ky: " << hocky << " - Nhom: " << nhom << "\n";
    cout << "\nSTT   MASV       HO             TEN        DIEM\n";
    PTRDK p = ltc->DSDK;
    PTRSV SV = NULL;
    bool found = false;
    float diem;
    int stt = 1;
    while (p != NULL)
    {
        SV = SearchSV_MASV(DSLSV, p->dk.MASV);
        cout << setw(3) << stt << "   ";
        cout << setw(10) << left << p->dk.MASV << " ";
        if (SV != NULL)
        {
            cout << setw(14) << left << SV->sv.HO << " ";
            cout << setw(10) << left << SV->sv.TEN << " ";
        }
        else
        {
            cout << setw(14) << left << "XXXXXXXXXXXX" << " ";
            cout << setw(10) << left << "XXXXX" << " ";
        }
        if (p->dk.DIEM > 0)
            cout << fixed << setprecision(1) << p->dk.DIEM;
        else
            cout << " ";
        cout << "\n";
        p = p->next;
        stt++;
    }
    p = ltc->DSDK;
    stt = 1;
    while (p != NULL)
    {
        SV = SearchSV_MASV(DSLSV, p->dk.MASV);
        cout << "\n--- Sinh vien ---\n";
        cout << "Ma SV: " << p->dk.MASV;
        if (SV != NULL)
        {
            cout << " - " << SV->sv.HO << " " << SV->sv.TEN << "\n";
        }
        else
        {
            cout << "Khong tim thay sinh vien co ma " << p->dk.MASV << " trong danh sach sinh vien\n";
        }
        cout << "Diem hien tai: " << (p->dk.DIEM > 0 ? to_string(p->dk.DIEM) : "Chua co diem") << "\n";
        cout << "Nhap diem moi (0-10): ";
        cin >> diem;
        while (diem < 0 || diem > 10)
        {
            cout << "Diem khong hop le! Nhap lai (0-10): ";
            cin >> diem;
        }
        p->dk.DIEM = diem;
        cout << "Da cap nhat diem thanh cong!\n";
        cout << "--------------------------------\n";
        p = p->next;
        stt++;
    }
    cout << "\nHoan thanh nhap diem cho lop tin chi!\n";
}
/*
void InDiemTB_KhoaHoc(DSLopSV &DSLSV, DSLopTC &DSLTC, TreeMH &DSMH)
{
    string malop;
    cout << "Nhap ma lop sinh vien: ";
    cin >> malop;
    int indexLop = -1;
    for (int i = 0; i < DSLSV.n; i++)
    {
        if (DSLSV.nodes[i].MALOP == malop)
        {
            indexLop = i;
            break;
        }
    }
    if (indexLop == -1)
    {
        cout << "Khong ton tai lop sinh vien nay!\n";
        return;
    }
    if (DSLSV.nodes[indexLop].FirstSV == NULL)
    {
        cout << "Lop sinh vien chua co sinh vien nao!\n";
        return;
    }
    cout << "BANG THONG KE DIEM TRUNG BINH KHOA HOC\n";
    cout << "Lop    : " << malop << "\n\n";
    cout << "| STT | MASV     |      HO       | TEN    | Diem TB |\n";
    cout << "|-----|----------|---------------|--------|---------|\n";
    PTRSV p = DSLSV.nodes[indexLop].FirstSV;
    int stt = 1;
    while (p != NULL)
    {
        float tongDiem = 0;
        int tongTinChi = 0;
        int soMonCoDiem = 0;
        for (int i = 0; i < DSLTC.n; i++)
        {
            if (DSLTC.nodes[i] != NULL && !DSLTC.nodes[i]->HUYLOP)
            {
                PTRDK dk = DSLTC.nodes[i]->DSDK;
                while (dk != NULL)
                {
                    if (dk->dk.MASV == p->sv.MASV && dk->dk.DIEM > 0)
                    {
                        int stc = SearchSTC_MAMH(DSMH, DSLTC.nodes[i]->MAMH);
                        if (stc > 0)
                        {
                            tongDiem += dk->dk.DIEM * stc;
                            tongTinChi += stc;
                            soMonCoDiem++;
                        }
                        break;
                    }
                    dk = dk->next;
                }
            }
        }
        cout << "| " << setw(2) << stt << "  | ";
        cout << setw(8) << left << p->sv.MASV << " | ";
        cout << setw(13) << left << p->sv.HO << " | ";
        cout << setw(6) << left << p->sv.TEN << " | ";
        if (tongTinChi > 0 && soMonCoDiem > 0)
        {
            float diemTB = tongDiem / tongTinChi;
            cout << setw(6) << fixed << setprecision(1) << diemTB << " |";
        }
        else
        {
            cout << setw(6) << " " << " |";
        }
        cout << "\n";
        p = p->next;
        stt++;
    }
}*/

void InDiemTongKet(DSLopSV &DSLSV, DSLopTC &DSLTC, TreeMH &DSMH)
{
    string malop;
    cout << "Nhap ma lop sinh vien: ";
    cin >> malop;
    int indexLop = -1;
    for (int i = 0; i < DSLSV.n; i++)
    {
        if (DSLSV.nodes[i].MALOP == malop)
        {
            indexLop = i;
            break;
        }
    }
    if (indexLop == -1)
    {
        cout << "Khong ton tai lop sinh vien nay!\n";
        return;
    }
    if (DSLSV.nodes[indexLop].FirstSV == NULL)
    {
        cout << "Lop sinh vien chua co sinh vien nao!\n";
        return;
    }
    string *danhSachMaMH = NULL;
    int soMon = 0;
    int capacity = 10;
    danhSachMaMH = new string[capacity];
    PTRSV p = DSLSV.nodes[indexLop].FirstSV;
    while (p != NULL)
    {
        for (int i = 0; i < DSLTC.n; i++)
        {
            if (DSLTC.nodes[i] != NULL && !DSLTC.nodes[i]->HUYLOP)
            {
                PTRDK dk = DSLTC.nodes[i]->DSDK;
                while (dk != NULL)
                {
                    if (dk->dk.MASV == p->sv.MASV && dk->dk.DIEM >= 0)
                    {
                        bool daTonTai = false;
                        for (int j = 0; j < soMon; j++)
                        {
                            if (danhSachMaMH[j] == DSLTC.nodes[i]->MAMH)
                            {
                                daTonTai = true;
                                break;
                            }
                        }
                        if (!daTonTai)
                        {
                            if (soMon >= capacity)
                            {
                                capacity *= 2;
                                string *temp = new string[capacity];

                                for (int k = 0; k < soMon; k++)
                                {
                                    temp[k] = danhSachMaMH[k];
                                }
                                delete[] danhSachMaMH;
                                danhSachMaMH = temp;
                            }
                            danhSachMaMH[soMon] = DSLTC.nodes[i]->MAMH;
                            soMon++;
                        }
                        break;
                    }
                    dk = dk->next;
                }
            }
        }
        p = p->next;
    }
    cout << "\n";
    cout << setw(50) << "BANG DIEM TONG KET\n";
    cout << setw(40) << "Lop : " << malop << "\n\n";
    cout << "| STT | Ma SV    | Ho Ten        |";
    for (int i = 0; i < soMon; i++)
    {
        cout << " " << setw(6) << danhSachMaMH[i] << " |";
    }
    cout << "\n";
    cout << "|-----|----------|---------------|";
    for (int i = 0; i < soMon; i++)
    {
        cout << "--------|";
    }
    cout << "\n";
    p = DSLSV.nodes[indexLop].FirstSV;
    int stt = 1;
    while (p != NULL)
    {
        cout << "| " << setw(2) << stt << "  | ";
        cout << setw(8) << left << p->sv.MASV << " | ";

        string hoTen = p->sv.HO + " " + p->sv.TEN;
        cout << setw(13) << left << hoTen << " |";
        for (int i = 0; i < soMon; i++)
        {
            float diem = -1;
            bool timThay = false;
            for (int j = 0; j < DSLTC.n; j++)
            {
                if (DSLTC.nodes[j] != NULL && !DSLTC.nodes[j]->HUYLOP &&
                    DSLTC.nodes[j]->MAMH == danhSachMaMH[i])
                {
                    PTRDK dk = DSLTC.nodes[j]->DSDK;
                    while (dk != NULL)
                    {
                        if (dk->dk.MASV == p->sv.MASV)
                        {
                            diem = dk->dk.DIEM;
                            timThay = true;
                            break;
                        }
                        dk = dk->next;
                    }
                    if (timThay)
                        break;
                }
            }
            if (timThay && diem >= 0)
            {
                cout << " " << setw(6) << fixed << setprecision(0) << diem << " |";
            }
            else
            {
                cout << " " << setw(6) << "" << " |";
            }
        }
        cout << "\n";
        p = p->next;
        stt++;
    }
    delete[] danhSachMaMH;
}

/*Tài*/

/*Tân*/
NodeMH *TaoNodeMH(MonHoc mh)
{
    NodeMH *p = new NodeMH;
    p->mh = mh;
    p->left = NULL;
    p->right = NULL;
    return p;
}

void ChenNodeMH(TreeMH &DSMH, MonHoc mh)
{
    if (DSMH == NULL)
    {
        DSMH = TaoNodeMH(mh);
        return;
    }
    if (SoSanh_Chuoi(mh.MAMH, DSMH->mh.MAMH) < 0)
    {
        ChenNodeMH(DSMH->left, mh);
    }
    else if (SoSanh_Chuoi(mh.MAMH, DSMH->mh.MAMH) > 0)
    {
        ChenNodeMH(DSMH->right, mh);
    }
    else
    {
        cout << "Ma mon hoc da ton tai!\n";
    }
}

string NhapSoNguyen(int maxDigits = 3){
	string input = "";
	char c;
	while (true){
		c = _getch();
		if(c==13) break;
		else if (c == 8 && !input.empty()){
			input.pop_back();
			cout<<"\b \b";
		}
		else if (isdigit(c) && (int)input.length() < maxDigits){
			input += c;
			cout << c;
		}
	}
	cout << endl;
	return input;
} 

TreeMH Search_MH(TreeMH root, string mamh) {
    if (root == NULL) return NULL;
    if (strcasecmp(root->mh.MAMH.c_str(), mamh.c_str()) == 0) return root;
    if (mamh < root->mh.MAMH) return Search_MH(root->left, mamh);
    else return Search_MH(root->right, mamh);
}

TreeMH Insert_MH(TreeMH root, MonHoc mh) {
    if (root == NULL) {
        TreeMH newNode = new NodeMH;
        newNode->mh = mh;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (mh.MAMH < root->mh.MAMH) root->left = Insert_MH(root->left, mh);
    else if (mh.MAMH > root->mh.MAMH) root->right = Insert_MH(root->right, mh);
    return root;
}
void Them_MonHoc(TreeMH &DSMH)
{
    MonHoc mh;
    cout << "Nhap ma mon hoc: ";
    cin >> mh.MAMH;
    mh.MAMH = ChuanHoa_Chuoi(mh.MAMH, 10);
    // Kiem tra trung ma mon hoc
    NodeMH *temp = DSMH;
    while (temp != NULL)
    {
        if (strcasecmp(temp->mh.MAMH.c_str(), mh.MAMH.c_str()) == 0)
        {
            cout << "Ma mon hoc da ton tai!\n";
            return;
        }
        if (SoSanh_Chuoi(mh.MAMH, temp->mh.MAMH) < 0)
            temp = temp->left;
        else
            temp = temp->right;
    }
    cout << "Nhap ten mon hoc: ";
    cin.ignore(1000, '\n');
    getline(cin, mh.TENMH);
    mh.TENMH = ChuanHoa_Chuoi(mh.TENMH, 50);
    cout << "Nhap so tin chi ly thuyet: ";
    cin >> mh.STCLT;
    cout << "Nhap so tin chi thuc hanh: ";
    cin >> mh.STCTH;
    ChenNodeMH(DSMH, mh);
    cout << "Them mon hoc thanh cong!\n";
}

NodeMH *TimMH_MAMH(TreeMH DSMH, string mamh)
{
    if (DSMH == NULL)
        return NULL;
    if (strcasecmp(DSMH->mh.MAMH.c_str(), mamh.c_str()) == 0)
        return DSMH;
    if (SoSanh_Chuoi(mamh, DSMH->mh.MAMH) < 0)
        return TimMH_MAMH(DSMH->left, mamh);
    return TimMH_MAMH(DSMH->right, mamh);
}

void HieuChinh_MonHoc(TreeMH &DSMH)
{
    if (DSMH == NULL)
    {
        cout << "Danh sach mon hoc rong!\n";
        return;
    }
    string mamh;
    cout << "Nhap ma mon hoc can hieu chinh: ";
    cin >> mamh;
    mamh = ChuanHoa_Chuoi(mamh, 10);
    NodeMH *node = TimMH_MAMH(DSMH, mamh);
    if (node == NULL)
    {
        cout << "Khong tim thay mon hoc!\n";
        return;
    }
    cout << "Thong tin hien tai:\n";
    cout << "Ma mon hoc: " << node->mh.MAMH << "\n";
    cout << "Ten mon hoc: " << node->mh.TENMH << "\n";
    cout << "So tin chi ly thuyet: " << node->mh.STCLT << "\n";
    cout << "So tin chi thuc hanh: " << node->mh.STCTH << "\n";
    cout << "Nhap ten mon hoc moi: ";
    cin.ignore(1000, '\n');
    getline(cin, node->mh.TENMH);
    node->mh.TENMH = ChuanHoa_Chuoi(node->mh.TENMH, 50);
    cout << "Nhap so tin chi ly thuyet moi: ";
    cin >> node->mh.STCLT;
    cout << "Nhap so tin chi thuc hanh moi: ";
    cin >> node->mh.STCTH;
    cout << "Hieu chinh mon hoc thanh cong!\n";
}

NodeMH *TimMinMH(TreeMH DSMH)
{
    while (DSMH != NULL && DSMH->left != NULL)
        DSMH = DSMH->left;
    return DSMH;
}

void Xoa_MonHoc(TreeMH &DSMH)
{
    if (DSMH == NULL)
    {
        cout << "Danh sach mon hoc rong!\n";
        return;
    }
    string mamh;
    cout << "Nhap ma mon hoc can xoa: ";
    cin >> mamh;
    mamh = ChuanHoa_Chuoi(mamh, 10);
    NodeMH *parent = NULL;
    NodeMH *current = DSMH;
    while (current != NULL && strcasecmp(current->mh.MAMH.c_str(), mamh.c_str()) != 0)
    {
        parent = current;
        if (SoSanh_Chuoi(mamh, current->mh.MAMH) < 0)
            current = current->left;
        else
            current = current->right;
    }
    if (current == NULL)
    {
        cout << "Khong tim thay ma mon hoc!\n";
        return;
    }
    cout << "Ban co chac chan muon xoa? (Y/N): ";
    string xacnhan;
    cin >> xacnhan;
    if (strcasecmp(xacnhan.c_str(), "Y") != 0)
    {
        cout << "Da huy thao tac!\n";
        return;
    }
    if (current->left == NULL)
    {
        if (current == DSMH)
        {
            DSMH = current->right;
        }
        else if (parent->left == current)
        {
            parent->left = current->right;
        }
        else
        {
            parent->right = current->right;
        }
        delete current;
    }
    else if (current->right == NULL)
    {
        if (current == DSMH)
        {
            DSMH = current->left;
        }
        else if (parent->left == current)
        {
            parent->left = current->left;
        }
        else
        {
            parent->right = current->left;
        }
        delete current;
    }
    else
    {
        NodeMH *minNode = TimMinMH(current->right);
        current->mh = minNode->mh;
        NodeMH *minParent = current;
        NodeMH *minCurrent = current->right;
        while (minCurrent != minNode)
        {
            minParent = minCurrent;
            minCurrent = minCurrent->left;
        }
        if (minParent->left == minCurrent)
            minParent->left = minCurrent->right;
        else
            minParent->right = minCurrent->right;
        delete minCurrent;
    }
    cout << "Xoa mon hoc thanh cong!\n";
}

// Luu tam thoi
struct DSMHArray
{
    MonHoc *nodes;
    int n;
    int capacity;
    DSMHArray()
    {
        capacity = 100;
        nodes = new MonHoc[capacity];
        n = 0;
    }
    ~DSMHArray()
    {
        delete[] nodes;
    }
    void Them(MonHoc mh)
    {
        if (n >= capacity)
        {
            int new_capacity = capacity * 2;
            MonHoc *new_nodes = new MonHoc[new_capacity];
            for (int i = 0; i < n; i++)
            {
                new_nodes[i] = nodes[i];
            }
            delete[] nodes;
            nodes = new_nodes;
            capacity = new_capacity;
        }
        nodes[n] = mh;
        n++;
    }
};

void ThuThapMH(TreeMH DSMH, DSMHArray &arr)
{
    if (DSMH != NULL)
    {
        ThuThapMH(DSMH->left, arr);
        arr.Them(DSMH->mh);
        ThuThapMH(DSMH->right, arr);
    }
}

void In_DSMH_SapXep(TreeMH DSMH)
{
    if (DSMH == NULL)
    {
        cout << "Danh sach mon hoc rong!\n";
        return;
    }
    DSMHArray arr;
    ThuThapMH(DSMH, arr);
    for (int i = 0; i < arr.n - 1; i++)
    {
        for (int j = i + 1; j < arr.n; j++)
        {
            if (SoSanh_Chuoi(arr.nodes[i].TENMH, arr.nodes[j].TENMH) > 0)
            {
                MonHoc temp = arr.nodes[i];
                arr.nodes[i] = arr.nodes[j];
                arr.nodes[j] = temp;
            }
        }
    }
    cout << "--- DANH SACH MON HOC (SAP XEP THEO TEN) ---\n";
    cout << "----------------------------------------------------------\n";
    cout << left
         << setw(10) << "Ma MH"
         << setw(35) << "Ten Mon Hoc"
         << setw(8) << "STCLT"
         << setw(8) << "STCTH" << "\n";
    cout << "----------------------------------------------------------\n";
    for (int i = 0; i < arr.n; i++)
    {
        cout << left
             << setw(10) << arr.nodes[i].MAMH
             << setw(35) << arr.nodes[i].TENMH
             << setw(8) << arr.nodes[i].STCLT
             << setw(8) << arr.nodes[i].STCTH << "\n";
    }
}

void InBangDiem_LopTC(DSLopTC &DSLTC, TreeMH &DSMH, DSLopSV &DSLSV)
{
    string mamh, nienkhoa;
    int hocky, nhom;
    cout << "Nhap ma mon hoc: ";
    cin >> mamh;
    cout << "Nhap nien khoa: ";
    cin >> nienkhoa;
    cout << "Nhap hoc ky: ";
    cin >> hocky;
    cout << "Nhap nhom: ";
    cin >> nhom;
    LopTC *ltc = SearchLopTC(DSLTC, mamh, nienkhoa, hocky, nhom);
    if (ltc == NULL || ltc->HUYLOP)
    {
        cout << "Khong ton tai lop tin chi nay hoac da bi huy!\n";
        return;
    }
    string tenmh = SearchTenMH_MAMH(DSMH, mamh);
    cout << "\nBẢNG ĐIỂM MÔN HỌC: " << tenmh << "\n";
    cout << "Niên khóa: " << nienkhoa << "  | Học kỳ: " << hocky << "  | Nhóm: " << nhom << "\n";
    cout << "-------------------------------------------------------------\n";
    cout << "STT  MASV        HO                 TEN        DIEM\n";
    cout << "-------------------------------------------------------------\n";
    int stt = 1;
    for (PTRDK p = ltc->DSDK; p != NULL; p = p->next)
    {
        PTRSV sv = SearchSV_MASV(DSLSV, p->dk.MASV);
        if (sv != NULL)
        {
            cout << setw(3) << stt << "  "
                 << setw(10) << sv->sv.MASV << "  "
                 << setw(18) << sv->sv.HO << "  "
                 << setw(10) << sv->sv.TEN << "  "
                 << fixed << setprecision(1) << p->dk.DIEM << "\n";
        }
        stt++;
    }
}
/*Tân*/

/*Doc File*/
void DocFile_DSMH(TreeMH &DSMH)
{
    ifstream in("DSMH.txt");
    if (!in.is_open())
    {
        cout << "Khong the mo file DSMH.txt\n";
        return;
    }
    string line;
    if (!getline(in, line))
    {
        cout << "File rong hoac sai dinh dang\n";
        return;
    }
    int soMonHoc = stoi(line);
    for (int i = 0; i < soMonHoc; ++i)
    {
        if (!getline(in, line))
            break;
        stringstream ss(line);
        string MAMH, TENMH, STCLT, STCTH;
        getline(ss, MAMH, ',');
        getline(ss, TENMH, ',');
        getline(ss, STCLT, ',');
        getline(ss, STCTH, ',');
        MonHoc mh;
        mh.MAMH = MAMH;
        mh.TENMH = TENMH;
        mh.STCLT = stoi(STCLT);
        mh.STCTH = stoi(STCTH);
        ChenNodeMH(DSMH, mh);
    }
    in.close();
}

int TimViTriLop(DSLopSV &DSLSV, string maLop)
{
    for (int i = 0; i < DSLSV.n; i++)
    {
        if (DSLSV.nodes[i].MALOP == maLop)
            return i;
    }
    return -1;
}

void ThemSinhVienVaoLop(PTRSV &FirstSV, SinhVien sv)
{
    PTRSV newNode = new NodeSV{sv, NULL};
    if (FirstSV == NULL)
    {
        FirstSV = newNode;
    }
    else
    {
        PTRSV temp = FirstSV;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

void DocFile_DSLSV(DSLopSV &DSLSV)
{
    ifstream in("DSLSV.txt");
    if (!in.is_open())
    {
        cout << "Khong the mo file DSLSV.txt\n";
        return;
    }
    string line;
    LopSV *lopHienTai = NULL;
    if (!getline(in, line))
    {
        cout << "File rong hoac sai dinh dang\n";
        return;
    }
    int soLop = stoi(line);
    for (int i = 0; i < soLop; ++i)
    {
        if (!getline(in, line))
            break;
        stringstream ss(line);
        string MALOP, TENLOP;
        getline(ss, MALOP, ',');
        getline(ss, TENLOP);
        LopSV lop;
        lop.MALOP = MALOP;
        lop.TENLOP = TENLOP;
        if (!getline(in, line))
            break;
        lop.SLSV = stoi(line);
        lop.FirstSV = NULL;
        lopHienTai = &DSLSV.nodes[DSLSV.n];
        *lopHienTai = lop;
        for (int j = 0; j < lop.SLSV; ++j)
        {
            if (!getline(in, line))
                break;
            line = line.substr(5);
            stringstream svStream(line);
            SinhVien sv;
            getline(svStream, sv.MASV, ',');
            getline(svStream, sv.HO, ',');
            getline(svStream, sv.TEN, ',');
            getline(svStream, sv.GIOITINH, ',');
            getline(svStream, sv.SODT, ',');
            getline(svStream, sv.EMAIL, ',');

            ThemSinhVienVaoLop(lopHienTai->FirstSV, sv);
        }

        DSLSV.n++;
    }
    in.close();
}

void DocFile_DSLTC(DSLopTC &DSLTC)
{
    ifstream in("DSLTC.txt");
    if (!in.is_open())
    {
        cout << "Khong the mo file DSLTC.txt\n";
        return;
    }
    string line;
    getline(in, line);
    int tongSoLop = stoi(line);
    for (int i = 0; i < tongSoLop; ++i)
    {
        if (!getline(in, line))
            break;
        stringstream ss(line);
        string MALOPTC, MAMH, NIENKHOA, HOCKY, NHOM, MINSV, MAXSV, HUYLOP;
        getline(ss, MALOPTC, ',');
        getline(ss, MAMH, ',');
        getline(ss, NIENKHOA, ',');
        getline(ss, HOCKY, ',');
        getline(ss, NHOM, ',');
        getline(ss, MINSV, ',');
        getline(ss, MAXSV, ',');
        getline(ss, HUYLOP, ',');
        LopTC *ltc = new LopTC;
        ltc->MALOPTC = stoi(MALOPTC);
        ltc->MAMH = MAMH;
        ltc->NIENKHOA = NIENKHOA;
        ltc->HOCKY = stoi(HOCKY);
        ltc->NHOM = stoi(NHOM);
        ltc->MINSV = stoi(MINSV);
        ltc->MAXSV = stoi(MAXSV);
        ltc->SLSVDK = 0;
        ltc->HUYLOP = (HUYLOP == "Yes");
        ltc->DSDK = NULL;
        if (!getline(in, line))
            break;
        int soSV = stoi(line);
        ltc->SLSVDK = soSV;
        for (int j = 0; j < soSV; ++j)
        {
            if (!getline(in, line))
                break;
            line = line.substr(5);
            stringstream svStream(line);
            string MASV, DIEM_STR;
            getline(svStream, MASV, ',');
            getline(svStream, DIEM_STR, ',');
            float DIEM = stof(DIEM_STR);
            PTRDK newNode = new NodeDK;
            newNode->dk.MASV = MASV;
            newNode->dk.DIEM = DIEM;
            newNode->next = NULL;
            if (ltc->DSDK == NULL)
            {
                ltc->DSDK = newNode;
            }
            else
            {
                PTRDK last = ltc->DSDK;
                while (last->next != NULL)
                    last = last->next;
                last->next = newNode;
            }
        }
        DSLTC.nodes[DSLTC.n++] = ltc;
    }
    in.close();
}

void DocFile(TreeMH &DSMH, DSLopSV &DSLSV, DSLopTC &DSLTC)
{
    DocFile_DSMH(DSMH);
    DocFile_DSLSV(DSLSV);
    DocFile_DSLTC(DSLTC);
    cout << "Doc du lieu tu file thanh cong!\n";
}
/*Doc File*/

/*Ghi File*/
int DemSoMonHoc(TreeMH DSMH)
{
    if (DSMH == NULL)
        return 0;
    return 1 + DemSoMonHoc(DSMH->left) + DemSoMonHoc(DSMH->right);
}

void GhiDSMH_NLR(TreeMH DSMH, ofstream &out)
{
    if (DSMH == NULL)
        return;
    out << DSMH->mh.MAMH << ","
        << DSMH->mh.TENMH << ","
        << DSMH->mh.STCLT << ","
        << DSMH->mh.STCTH << "\n";
    GhiDSMH_NLR(DSMH->left, out);
    GhiDSMH_NLR(DSMH->right, out);
}

void GhiFile_DSMH(TreeMH &DSMH)
{
    ofstream out("DSMH_Temp.txt");
    if (!out.is_open())
    {
        cout << "Khong the mo file DSMH_Temp.txt\n";
        return;
    }
    int soMonHoc = DemSoMonHoc(DSMH);
    out << soMonHoc << "\n";
    GhiDSMH_NLR(DSMH, out);
    out.close();
}

void GhiFile_DSLSV(DSLopSV &DSLSV)
{
    ofstream out("DSLSV_Temp.txt");
    if (!out.is_open())
    {
        cout << "Khong the mo file DSLSV_Temp.txt\n";
        return;
    }
    out << DSLSV.n << "\n";
    for (int i = 0; i < DSLSV.n; i++)
    {
        LopSV &lop = DSLSV.nodes[i];
        out << lop.MALOP << "," << lop.TENLOP << "\n";
        out << "     " << lop.SLSV << "\n";
        for (PTRSV p = lop.FirstSV; p != NULL; p = p->next)
        {
            SinhVien &sv = p->sv;
            out << "     "
                << sv.MASV << ","
                << sv.HO << ","
                << sv.TEN << ","
                << sv.GIOITINH << ","
                << sv.SODT << ","
                << sv.EMAIL << "\n";
        }
    }
    out.close();
}

void GhiFile_DSLTC(DSLopTC &DSLTC)
{
    ofstream out("DSLTC_Temp.txt");
    if (!out.is_open())
    {
        cout << "Khong the mo file DSLTC_Temp.txt\n";
        return;
    }
    out << DSLTC.n << "\n";
    for (int i = 0; i < DSLTC.n; ++i)
    {
        LopTC *ltc = DSLTC.nodes[i];
        out << ltc->MALOPTC << "," << ltc->MAMH << "," << ltc->NIENKHOA << "," << ltc->HOCKY << "," << ltc->NHOM << ","
            << ltc->MINSV << "," << ltc->MAXSV << "," << (ltc->HUYLOP ? "Yes" : "No") << "\n";
        int countSV = 0;
        for (PTRDK p = ltc->DSDK; p != NULL; p = p->next)
            countSV++;
        out << "     " << countSV << "\n";
        PTRDK p = ltc->DSDK;
        int stt = 1;
        while (p != NULL)
        {
            out << "     " << p->dk.MASV << "," << fixed << setprecision(1) << p->dk.DIEM << "\n";
            p = p->next;
        }
    }
    out.close();
}

void GhiFile(TreeMH &DSMH, DSLopSV &DSLSV, DSLopTC &DSLTC)
{
    GhiFile_DSMH(DSMH);
    GhiFile_DSLSV(DSLSV);
    GhiFile_DSLTC(DSLTC);
    cout << "Da ghi du lieu vao file thanh cong!\n";
}
/*Ghi File*/

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
        cout << "6. Liet ke danh sach sinh vien\n";
        cout << "7. Them lop sinh vien\n";
        cout << "8. Xoa lop sinh vien\n";
        cout << "9. Hieu chinh lop sinh vien\n";
        cout << "10. Nhap sinh vien vao lop\n";
        cout << "11. Liet ke lop sinh vien\n";
        cout << "12. In DSSV lop sap xep theo ten+ho\n";
        cout << "13. In DSSV da dang ky theo lop tin chi\n";
        cout << "14. Them mon hoc\n";
        cout << "15. Xoa mon hoc\n";
        cout << "16. Hieu chinh mon hoc\n";
        cout << "17. In danh sach mon hoc theo ten tang dan\n";
        cout << "18. Doc file\n";
        cout << "19. Ghi file\n";
        cout << "20. Dang ky lop tin chi\n";
        cout << "21. In DSSV da dang ky theo lop tin chi\n";
        cout << "22. Nhap diem cho lop tin chi\n";
        cout << "23. In diem trung binh cua 1 lop tin chi\n";
        cout << "24. In bang diem sinh vien theo ma lop sinh vien\n";
        cout << "25. In bang diem mon hoc cua lop tin chi\n";
        cout << "0. Thoat\n";
        int choice;
        cout << "Nhap lua chon: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            Them_LopTC(DSLTC, DSMH);
            break;
        case 2:
            LietKe_LopTC(DSLTC, DSMH);
            break;
        case 3:
            Xoa_LopTC(DSLTC);
            break;
        case 4:
            HieuChinh_LopTC(DSLTC);
            break;
        case 5:
            break;
        case 6:
            LietKe_DSSV(DSLSV);
            break;
        case 7:
            Them_LopSV(DSLSV);
            break;
        case 8:
            Xoa_LopSV(DSLSV);
            break;
        case 9:
            HieuChinh_LopSV(DSLSV);
            break;
        case 10:
            Nhap_SV_Lop(DSLSV, FirstSV);
            break;
        case 11:
            LietKe_LopSV(DSLSV);
            break;
        case 12:
            In_DSSV_Lop_SapXep(DSLSV);
            break;
        case 13:
            Them_LopSV(DSLSV);
            break;
        case 14:
            Them_MonHoc(DSMH);
            break;
        case 15:
            Xoa_MonHoc(DSMH);
            break;
        case 16:
            HieuChinh_MonHoc(DSMH);
            break;
        case 17:
            In_DSMH_SapXep(DSMH);
            break;
        case 18:
            DocFile(DSMH, DSLSV, DSLTC);
            break;
        case 19:
            GhiFile(DSMH, DSLSV, DSLTC);
            break;
        case 20:
            DangKy_LopTC(DSLTC, DSMH, DSLSV);
            break;
        case 21:
            InDSSV_LopTC(DSLTC, DSLSV);
            break;
        case 22:
            NhapDiem_LopTC(DSLTC, DSMH, DSLSV);
            break;
        case 23:
            // InDiemTB_LopTC(DSLTC, DSMH);
            break;
        case 24:
            InDiemTongKet(DSLSV, DSLTC, DSMH);
            break;
        case 25:
            InBangDiem_LopTC(DSLTC, DSMH, DSLSV);
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
