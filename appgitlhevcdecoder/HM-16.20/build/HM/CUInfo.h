#pragma once
#include <vector>
#include <fstream>
class CUInfo {
public:
    void push_cupu(signed char val) {
        m_cupuInfo.push_back(val);
    }
    void push_tu(signed char val) {
        m_tuInfo.push_back(val);
    }
    void push_pred(signed char val) {
        m_predInfo.push_back(val);
    }
    void push_mv(signed char val) {
        m_mvInfo.push_back(val);
    }
    void push_merge(signed char val) {
        m_mergeInfo.push_back(val);
    }
    void push_intra(signed char val) {
        m_intraInfo.push_back(val);
    }
    void push_bitLCU(short val) {
        m_bitLCUInfo.push_back(val);
    }
    void push_bitSCU(short val) {
        m_bitSCUInfo.push_back(val);
    }
    void write_cupu(std::ofstream& of) const {
        write_vec_var(of, m_cupuInfo);
    }
    void write_tu(std::ofstream& of) const {
        write_vec_var(of, m_tuInfo);
    }
    void write_pred(std::ofstream& of) const {
        write_vec_var(of, m_predInfo);
    }
    void write_mv(std::ofstream& of) const {
        write_vec_var(of, m_mvInfo);
    }
    void write_merge(std::ofstream& of) const {
        write_vec_var(of, m_mergeInfo);
    }
    void write_intra(std::ofstream& of) const {
        write_vec_var(of, m_intraInfo);
    }
    void write_bitLCU(std::ofstream& of) const {
        write_vec(of, m_bitLCUInfo);
    }
    void write_bitSCU(std::ofstream& of) const {
        write_vec_var(of, m_bitSCUInfo);
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
    std::vector<signed char> m_mvInfo;
    std::vector<signed char> m_mergeInfo;
    std::vector<signed char> m_intraInfo;
    std::vector<short> m_bitLCUInfo;
    std::vector<short> m_bitSCUInfo;
    template<typename T>
    static void write_vec_var(std::ofstream& of, const std::vector<T>& v) {
        assert(v.size() < 128);
        char sz = (char)v.size();
        of.write(&sz, sizeof(char));
        write_vec(of, v);
    }
    template<typename T>
    static void write_vec(std::ofstream& of, const std::vector<T>& v) {
        for (auto& i : v) {
            of.write((char*)&i, sizeof(T));
        }
    }
};