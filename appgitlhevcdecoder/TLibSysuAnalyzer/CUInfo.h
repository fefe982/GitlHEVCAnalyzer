#pragma once
#include <vector>
#include <fstream>
#include <limits>

enum class CUInfoParts {
    CUPU,
    TU,
    PRED,
    MV,
    MERGE,
    INTRA,
    BIT_LCU,
    BIT_SCU,
    N_PARTS
};

template<CUInfoParts Part>
struct CUInfoPartTrait {
    typedef signed char value_type;
    static const int len = 0;
};

template<>
struct CUInfoPartTrait<CUInfoParts::MV> {
    typedef short value_type;
    static const int len = 0;
};

template<>
struct CUInfoPartTrait<CUInfoParts::BIT_LCU> {
    typedef short value_type;
    static const int len = 1;
};

template<>
struct CUInfoPartTrait<CUInfoParts::BIT_SCU> {
    typedef short value_type;
    static const int len = 0;
};

class CUInfo {
public:
    void push_cupu(int val) {
        push(m_cupuInfo, val);
    }
    void push_tu(int val) {
        push(m_tuInfo, val);
    }
    void push_pred(int val) {
        push(m_predInfo, val);
    }
    void push_mv(int val) {
        push(m_mvInfo, val);
    }
    void push_merge(int val) {
        push(m_mergeInfo, val);
    }
    void push_intra(int val) {
        push(m_intraInfo, val);
    }
    void push_bitLCU(int val) {
        push(m_bitLCUInfo, val);
    }
    void push_bitSCU(int val) {
        push(m_bitSCUInfo, val);
    }
    void write_cupu(std::ofstream& of) const {
        write_vec<CUInfoParts::CUPU>(of, m_cupuInfo);
    }
    void write_tu(std::ofstream& of) const {
        write_vec<CUInfoParts::TU>(of, m_tuInfo);
    }
    void write_pred(std::ofstream& of) const {
        write_vec<CUInfoParts::PRED>(of, m_predInfo);
    }
    void write_mv(std::ofstream& of) const {
        write_vec<CUInfoParts::MV>(of, m_mvInfo);
    }
    void write_merge(std::ofstream& of) const {
        write_vec<CUInfoParts::MERGE>(of, m_mergeInfo);
    }
    void write_intra(std::ofstream& of) const {
        write_vec<CUInfoParts::INTRA>(of, m_intraInfo);
    }
    void write_bitLCU(std::ofstream& of) const {
        write_vec<CUInfoParts::BIT_LCU>(of, m_bitLCUInfo);
    }
    void write_bitSCU(std::ofstream& of) const {
        write_vec<CUInfoParts::BIT_SCU>(of, m_bitSCUInfo);
    }
    void write_all(std::ofstream& of) const {
        write_cupu(of);
        write_tu(of);
        write_pred(of);
        write_mv(of);
        write_merge(of);
        write_intra(of);
        write_bitLCU(of);
        write_bitSCU(of);
    }
private:
    std::vector<signed char> m_cupuInfo;
    std::vector<signed char> m_tuInfo;
    std::vector<signed char> m_predInfo;
    std::vector<short> m_mvInfo;
    std::vector<signed char> m_mergeInfo;
    std::vector<signed char> m_intraInfo;
    std::vector<short> m_bitLCUInfo;
    std::vector<short> m_bitSCUInfo;
    template<CUInfoParts Part>
    static void write_vec(std::ofstream& of, const std::vector<typename CUInfoPartTrait<Part>::value_type>& v) {
        assert(v.size() < 128);
        if constexpr (CUInfoPartTrait<Part>::len == 0) {
            char sz = (char)v.size();
            of.write(&sz, sizeof(char));
        }
        for (auto& i : v) {
            of.write((char*)&i, sizeof(typename CUInfoPartTrait<Part>::value_type));
        }
    }
    template<typename T>
    static void push(std::vector<T>& v, int val) {
        assert(val >= std::numeric_limits<T>::min() && val < std::numeric_limits<T>::max());
        v.push_back(val);
    }
};