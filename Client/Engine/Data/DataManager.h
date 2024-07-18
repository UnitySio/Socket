#pragma once
#include "Singleton.h"

class DataManager
{
public:
    DataManager() = default;
    ~DataManager() = default;

    /**
     * \brief 레지스트리의 모든 값을 삭제합니다.
     */
    static void DeleteAll();

    /**
     * \brief 키를 삭제합니다.
     * \param kKey 키
     */
    static void DeleteKey(const std::wstring& kKey);

    /**
     * \brief 키가 존재하는지 확인합니다.
     * \param kKey 키
     * \return bool
     */
    static bool HasKey(const std::wstring& kKey);

    /**
     * \brief int 형의 값을 레지스트리에 저장합니다.
     * \param kKey 키
     * \param value 값
     */
    static void SetInt(const std::wstring& kKey, int value);

    /**
     * \brief float 형의 값을 레지스트리에 저장합니다.
     * \param kKey 키
     * \param value 값
     */
    static void SetFloat(const std::wstring& kKey, float value);

    /**
     * \brief std::wstring 형의 값을 레지스트리에 저장합니다.
     * \param kKey 키
     * \param kValue 값
     */
    static void SetString(const std::wstring& kKey, const std::wstring& kValue);

    /**
     * \brief int 형의 값을 레지스트리에서 가져옵니다.
     * \param kKey 키
     * \param kDefaultValue 기본값
     * \return int
     */
    static int GetInt(const std::wstring& kKey, int kDefaultValue = 0);

    /**
     * \brief float 형의 값을 레지스트리에서 가져옵니다.
     * \param kKey 키
     * \param kDefaultValue 기본값
     * \return float
     */
    static float GetFloat(const std::wstring& kKey, float kDefaultValue = 0.f);

    /**
     * \brief std::wstring 형의 값을 레지스트리에서 가져옵니다.
     * \param kKey 키
     * \param kDefaultValue 기본값
     * \return std::wstring
     */
    static std::wstring GetString(const std::wstring& kKey, const std::wstring& kDefaultValue = L"");
};
