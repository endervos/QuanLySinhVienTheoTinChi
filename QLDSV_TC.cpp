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
        
        if (c1 < c2) return -1;
        if (c1 > c2) return 1;
    }
    
    if (len1 < len2) return -1;
    if (len1 > len2) return 1;
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
        case 0:
            check = false;
            break;
        default:
            cout << "Nhap sai! Nhap lai!\n";
            break;
        }
    }
}