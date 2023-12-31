#pragma once

#include <hjson.h>

#include <deque>
#include <string>
#include <vector>

bool load_json(Hjson::Value& json, std::string_view text);
bool load_json_file(Hjson::Value& json, const std::string_view filename);
bool save_json(const Hjson::Value& json, const std::string_view filename, bool no_space = false,
               bool append = false);
void merge_json(Hjson::Value& base, const Hjson::Value& add, bool overwrite = true);
bool check_property_string(const char* parser, const Hjson::Value& o, const char* prop);
bool check_property_obj(const char* parser, const Hjson::Value& o, const char* prop);
bool check_property_bool(const char* parser, const Hjson::Value& o, const char* prop);

void get_property_int(const Hjson::Value& o, int& val);
void get_property_float(const Hjson::Value& o, float& val);
void get_property_bool(const Hjson::Value& o, bool& val, bool default_value = false);

bool get_value_int(const Hjson::Value& doc, int8_t& val);
bool get_value_int(const Hjson::Value& doc, int16_t& val);
bool get_value_int(const Hjson::Value& doc, int32_t& val);
bool get_value_int(const Hjson::Value& doc, int64_t& val);
bool get_value_uint(const Hjson::Value& doc, uint8_t& val);
bool get_value_uint(const Hjson::Value& doc, uint16_t& val);
bool get_value_uint(const Hjson::Value& doc, uint32_t& val);
bool get_value_uint(const Hjson::Value& doc, uint64_t& val);
bool get_value_float(const Hjson::Value& doc, float& val);
bool get_value_double(const Hjson::Value& doc, double& val);
bool get_value_bool(const Hjson::Value& doc, bool& val);
bool get_value_string(const Hjson::Value& doc, std::string& val);
bool get_value_vector(const Hjson::Value& o, std::vector<int8_t>& val);
bool get_value_vector(const Hjson::Value& o, std::vector<int16_t>& val);
bool get_value_vector(const Hjson::Value& o, std::vector<int32_t>& val);
bool get_value_vector(const Hjson::Value& o, std::vector<int64_t>& val);
bool get_value_vector(const Hjson::Value& o, std::vector<uint8_t>& val);
bool get_value_vector(const Hjson::Value& o, std::vector<uint16_t>& val);
bool get_value_vector(const Hjson::Value& o, std::vector<uint32_t>& val);
bool get_value_vector(const Hjson::Value& o, std::vector<uint64_t>& val);
bool get_value_vector(const Hjson::Value& o, std::vector<float>& val);
bool get_value_vector(const Hjson::Value& o, std::vector<double>& val);
bool get_value_bool_deque(const Hjson::Value& o, std::deque<bool>& val);
bool get_value_vector(const Hjson::Value& o, std::vector<std::string>& val);

bool get_member_int(const Hjson::Value& doc, const std::string& objName, int8_t& val);
bool get_member_int(const Hjson::Value& doc, const std::string& objName, int16_t& val);
bool get_member_int(const Hjson::Value& doc, const std::string& objName, int32_t& val);
bool get_member_int(const Hjson::Value& doc, const std::string& objName, int64_t& val);
bool get_member_uint(const Hjson::Value& doc, const std::string& objName, uint8_t& val);
bool get_member_uint(const Hjson::Value& doc, const std::string& objName, uint16_t& val);
bool get_member_uint(const Hjson::Value& doc, const std::string& objName, uint32_t& val);
bool get_member_uint(const Hjson::Value& doc, const std::string& objName, uint64_t& val);
bool get_member_float(const Hjson::Value& doc, const std::string& objName, float& val);
bool get_member_double(const Hjson::Value& doc, const std::string& objName, double& val);
bool get_member_bool(const Hjson::Value& doc, const std::string& objName, bool& val);
bool get_member_bool_relaxed(const Hjson::Value& doc, const std::string& objName, bool& val);
bool get_member_string(const Hjson::Value& doc, const std::string& objName, std::string& val);
bool get_member_vector(const Hjson::Value& doc, const std::string& objName, std::vector<int8_t>& val);
bool get_member_vector(const Hjson::Value& doc, const std::string& objName, std::vector<int16_t>& val);
bool get_member_vector(const Hjson::Value& doc, const std::string& objName, std::vector<int32_t>& val);
bool get_member_vector(const Hjson::Value& doc, const std::string& objName, std::vector<int64_t>& val);
bool get_member_vector(const Hjson::Value& doc, const std::string& objName, std::vector<uint8_t>& val);
bool get_member_vector(const Hjson::Value& doc, const std::string& objName, std::vector<uint16_t>& val);
bool get_member_vector(const Hjson::Value& doc, const std::string& objName, std::vector<uint32_t>& val);
bool get_member_vector(const Hjson::Value& doc, const std::string& objName, std::vector<uint64_t>& val);
bool get_member_vector(const Hjson::Value& doc, const std::string& objName, std::vector<float>& val);
bool get_member_vector(const Hjson::Value& doc, const std::string& objName, std::vector<double>& val);
bool get_member_bool_deque(const Hjson::Value& doc, const std::string& objName, std::deque<bool>& val);
bool get_member_vector(const Hjson::Value& doc, const std::string& objName, std::vector<std::string>& val);

bool has_member(const Hjson::Value& doc, const std::string& objName);
