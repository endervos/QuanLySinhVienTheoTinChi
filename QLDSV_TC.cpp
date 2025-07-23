#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>

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

/*Tiến*/
PTRSV SearchSV_MASV(PTRSV &FirstSV, string msv)
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
        if (sv.MASV == "")
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
        cout << "Nhap ma sinh vien (de trong la dung nhap): ";
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
             << p->sv.GIOITINH << "\t\t"
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

void LietKe_LopTC(DSLopTC &DSLTC)
{
    cout << "--- DANH SACH LOP TIN CHI ---\n";
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
             << (ltc->HUYLOP ? "Yes" : "No") << "\n";
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

void InDSSV_LopTC(DSLopTC &DSLTC, PTRSV &FirstSV)
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
    cout << "DANH SACH SINH VIEN DANG KY LOP TIN CHI\n";
    cout << "-------------------------------------------------------------\n";
    cout << "MASV\t\tHO\t\tTEN\tGIOITINH\tSO DT\t\tEMAIL\n";
    NodeDK *p = ltc->DSDK;
    while (p != NULL)
    {
        PTRSV node = SearchSV_MASV(FirstSV, p->dk.MASV);
        if (node != NULL)
        {
            cout << node->sv.MASV << "\t" << node->sv.HO << "\t\t" << node->sv.TEN << "\t" << node->sv.GIOITINH << "\t\t" << node->sv.SODT << "\t" << node->sv.EMAIL << "\n";
        }
        p = p->next;
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

void DangKy_LopTC(DSLopTC &DSLTC, TreeMH &DSMH, PTRSV &FirstSV)
{
    string masv;
    cout << "Nhap ma sinh vien: ";
    cin >> masv;
    PTRSV p = SearchSV_MASV(FirstSV, masv);
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
    cout << "-------------------------------------------------------------\n";
    cout << "MaMH\tTenMH\t\tNhom\tSo SV Da DK\tCon Trong\n";
    for (int i = 0; i < DSLTC.n; i++)
    {
        LopTC *ltc = DSLTC.nodes[i];
        if (strcasecmp(ltc->NIENKHOA.c_str(), nienkhoa.c_str()) == 0 && ltc->HOCKY == hocky && ltc->HUYLOP == false)
        {
            string tenmh = SearchTenMH_MAMH(DSMH, ltc->MAMH);
            cout << ltc->MAMH << "\t" << tenmh << "\t\t" << ltc->NHOM << "\t" << ltc->SLSVDK << "\t\t" << ltc->MAXSV - ltc->SLSVDK << "\n";
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

void Nhap_SV_Lop(DSLopSV &DSLSV)
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
    cout << "Nhap sinh vien vao lop " << DSLSV.nodes[pos].TENLOP << ":\n";
    Nhap_DSSV(DSLSV.nodes[pos].FirstSV);
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
    cout << "STT\tMa Lop\t\tTen Lop\t\tSo SV\n";
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
    cout << "\nDANH SACH SINH VIEN LOP " << DSLSV.nodes[pos].TENLOP << " (sap xep theo ten+ho):\n";
    cout << "-------------------------------------------------------------\n";
    cout << "STT\tMaSV\t\tHo\t\tTen\t\tGioiTinh\tSoDT\t\tEmail\n";
    cout << "-------------------------------------------------------------\n";
    int stt = 1;
    for (PTRSV p = DSLSV.nodes[pos].FirstSV; p != NULL; p = p->next)
    {
        cout << stt << "\t"
             << p->sv.MASV << "\t\t"
             << p->sv.HO << "\t\t"
             << p->sv.TEN << "\t\t"
             << p->sv.GIOITINH << "\t\t"
             << p->sv.SODT << "\t\t"
             << p->sv.EMAIL << "\n";
        stt++;
    }
}

void NhapDiem_LopTC(DSLopTC &DSLTC, TreeMH &DSMH, PTRSV &FirstSV)
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
	cout << "\nNHAP DIEM LOP TIN CHI\n";
	cout << "Mon hoc: " << mamh << " - " << tenmh << "\n";
    cout << "Nien khoa: " << nienkhoa << " - Hoc ky: " << hocky << " - Nhom: " << nhom << "\n";
    
    PTRDK p = ltc->DSDK;
    PTRSV SV = NULL;
    bool found = false;
    float diem;
    
    while (p != NULL)
    {
    	SV = NULL;
    	found = false;
    	
    	SV = SearchSV_MASV(FirstSV, p->dk.MASV);
    	if (SV != NULL) 
    	{
    		found = true;
    	}
		
		cout << "\n--- Sinh vien ---\n";
		cout << "Ma SV: " << p->dk.MASV;
		
		if (found && SV != NULL)
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
	}
	
	cout << "\nHoan thanh nhap diem cho lop tin chi!\n";
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
    cout << "-------------------------------------------------------------\n";
    cout << "Ma MH\t\tTen Mon Hoc\t\t\tSTCLT\tSTCTH\n";
    cout << "-------------------------------------------------------------\n";
    for (int i = 0; i < arr.n; i++)
    {
        cout << arr.nodes[i].MAMH << "\t\t"
             << arr.nodes[i].TENMH;
        for (size_t j = arr.nodes[i].TENMH.length(); j < 30; j++)
            cout << " ";
        cout << arr.nodes[i].STCLT << "\t"
             << arr.nodes[i].STCTH << "\n";
    }
}

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
    while (getline(in, line))
    {
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

void DocFile_DSSV(PTRSV &FirstSV)
{
    ifstream in("DSSV.txt");
    if (!in.is_open())
    {
        cout << "Khong the mo file DSSV.txt\n";
        return;
    }
    string line;
    while (getline(in, line))
    {
        stringstream ss(line);
        string MASV, HO, TEN, GIOITINH, SODT, EMAIL;
        getline(ss, MASV, ',');
        getline(ss, HO, ',');
        getline(ss, TEN, ',');
        getline(ss, GIOITINH, ',');
        getline(ss, SODT, ',');
        getline(ss, EMAIL, ',');
        SinhVien sv;
        sv.MASV = MASV;
        sv.HO = HO;
        sv.TEN = TEN;
        sv.GIOITINH = GIOITINH;
        sv.SODT = SODT;
        sv.EMAIL = EMAIL;
        PTRSV newSV = new NodeSV;
        newSV->sv = sv;
        newSV->next = NULL;
        if (FirstSV == NULL)
        {
            FirstSV = newSV;
        }
        else
        {
            PTRSV temp = FirstSV;
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newSV;
        }
    }
    in.close();
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
    while (getline(in, line))
    {
        stringstream ss(line);
        string MALOP, TENLOP;
        getline(ss, MALOP, ',');
        getline(ss, TENLOP, ',');
        LopSV lopsv;
        lopsv.MALOP = MALOP;
        lopsv.TENLOP = TENLOP;
        lopsv.FirstSV = NULL;
        if (DSLSV.n >= DSLSV.capacity)
        {
            cout << "Danh sach lop sinh vien da day!\n";
            return;
        }
        DSLSV.nodes[DSLSV.n] = lopsv;
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
    while (getline(in, line))
    {
        stringstream ss(line);
        string MALOPTC, MAMH, NIENKHOA, HOCKY, NHOM, MINSV, MAXSV, SLSVDK, HUYLOP;
        getline(ss, MALOPTC, ',');
        getline(ss, MAMH, ',');
        getline(ss, NIENKHOA, ',');
        getline(ss, HOCKY, ',');
        getline(ss, NHOM, ',');
        getline(ss, MINSV, ',');
        getline(ss, MAXSV, ',');
        getline(ss, SLSVDK, ',');
        getline(ss, HUYLOP, ',');
        LopTC *ltc = new LopTC;
        ltc->MALOPTC = stoi(MALOPTC);
        ltc->MAMH = MAMH;
        ltc->NIENKHOA = NIENKHOA;
        ltc->HOCKY = stoi(HOCKY);
        ltc->NHOM = stoi(NHOM);
        ltc->MINSV = stoi(MINSV);
        ltc->MAXSV = stoi(MAXSV);
        ltc->SLSVDK = stoi(SLSVDK);
        ltc->HUYLOP = (HUYLOP == "Yes");
        DSLTC.nodes[DSLTC.n] = ltc;
        DSLTC.n++;
    }
    in.close();
}

void DocFile(TreeMH &DSMH, PTRSV &FirstSV, DSLopSV &DSLSV, DSLopTC &DSLTC)
{
    DocFile_DSMH(DSMH);
    DocFile_DSSV(FirstSV);
    DocFile_DSLSV(DSLSV);
    DocFile_DSLTC(DSLTC);
    cout << "Doc du lieu tu file thanh cong!\n";
}
/*Doc File*/

/*Ghi File*/
void GhiFile_DSMH(TreeMH &DSMH)
{
    ofstream out("DSMH.txt", ios::app);
    if (!out.is_open())
    {
        cout << "Khong the mo file DSMH.txt\n";
        return;
    }
    if (DSMH != NULL)
    {
        out << DSMH->mh.MAMH << ","
            << DSMH->mh.TENMH << ","
            << DSMH->mh.STCLT << ","
            << DSMH->mh.STCTH << "\n";
        GhiFile_DSMH(DSMH->left);
        GhiFile_DSMH(DSMH->right);
    }
    out.close();
}

void GhiFile_DSLSV(DSLopSV &DSLSV)
{
    ofstream out("DSLSV.txt");
    if (!out.is_open())
    {
        cout << "Khong the mo file DSLSV.txt\n";
        return;
    }
    for (int i = 0; i < DSLSV.n; i++)
    {
        out << DSLSV.nodes[i].MALOP << ","
            << DSLSV.nodes[i].TENLOP << "\n";
    }
    out.close();
}

void GhiFile_DSLTC(DSLopTC &DSLTC)
{
    ofstream out("DSLTC.txt");
    if (!out.is_open())
    {
        cout << "Khong the mo file DSLTC.txt\n";
        return;
    }
    for (int i = 0; i < DSLTC.n; i++)
    {
        LopTC *ltc = DSLTC.nodes[i];
        out << ltc->MALOPTC << ","
            << ltc->MAMH << ","
            << ltc->NIENKHOA << ","
            << ltc->HOCKY << ","
            << ltc->NHOM << ","
            << ltc->MINSV << ","
            << ltc->MAXSV << ","
            << ltc->SLSVDK << ","
            << (ltc->HUYLOP ? "Yes" : "No") << "\n";
    }
    out.close();
}

void GhiFile_DSSV(PTRSV &FirstSV)
{
    ofstream out("DSSV.txt");
    if (!out.is_open())
    {
        cout << "Khong the mo file DSSV.txt\n";
        return;
    }
    for (PTRSV p = FirstSV; p != NULL; p = p->next)
    {
        out << p->sv.MASV << ","
            << p->sv.HO << ","
            << p->sv.TEN << ","
            << p->sv.GIOITINH << ","
            << p->sv.SODT << ","
            << p->sv.EMAIL << "\n";
    }
    out.close();
}

void GhiFile_DSDK(PTRDK &FirstDK)
{
    ofstream out("DSDK.txt");
    if (!out.is_open())
    {
        cout << "Khong the mo file DSDK.txt\n";
        return;
    }
    for (PTRDK p = FirstDK; p != NULL; p = p->next)
    {
        out << p->dk.MASV << ","
            << p->dk.DIEM << "\n";
    }
    out.close();
}

void GhiFile(TreeMH &DSMH, PTRSV &FirstSV, DSLopSV &DSLSV, DSLopTC &DSLTC)
{
    GhiFile_DSMH(DSMH);
    GhiFile_DSSV(FirstSV);
    GhiFile_DSLSV(DSLSV);
    GhiFile_DSLTC(DSLTC);
    for (int i = 0; i < DSLTC.n; i++)
    {
        GhiFile_DSDK(DSLTC.nodes[i]->DSDK);
    }
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
        cout << "5. Nhap danh sach sinh vien\n";
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
            Xoa_LopTC(DSLTC);
            break;
        case 4:
            HieuChinh_LopTC(DSLTC);
            break;
        case 5:
            Nhap_DSSV(FirstSV);
            break;
        case 6:
            LietKe_DSSV(FirstSV);
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
            Nhap_SV_Lop(DSLSV);
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
            DocFile(DSMH, FirstSV, DSLSV, DSLTC);
            break;
        case 19:
            GhiFile(DSMH, FirstSV, DSLSV, DSLTC);
            break;
        case 20:
            DangKy_LopTC(DSLTC, DSMH, FirstSV);
            break;
        case 21:
            InDSSV_LopTC(DSLTC, FirstSV);
            break;
        case 22:
            NhapDiem_LopTC(DSLTC, DSMH, FirstSV);
            break;
        case 23:
            //InDiemTB_LopTC(DSLTC, DSMH);
            break;
        case 24:
            //InBangDiem_SV_TheoLop(DSLSV, DSLTC, DSMH);
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