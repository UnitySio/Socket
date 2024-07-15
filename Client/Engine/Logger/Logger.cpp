#include "pch.h"
#include "Logger.h"

#include "imgui/imgui.h"

Logger::Logger() :
    logs_()
{
}

void Logger::Render()
{
    ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Output Log"))
    {
        ImGui::End();
        return;
    }

    if (ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar))
    {
        for (const auto& log : logs_)
        {
            ImGui::Text(log.c_str());
        }
        
        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) ImGui::SetScrollHereY(1.f);
    }

    ImGui::EndChild();
    ImGui::End();

}

void Logger::AddLog(std::wstring format, ...)
{
    va_list args;
    va_start(args, format);

    wchar_t buffer[256];
    vswprintf_s(buffer, format.c_str(), args);
    wcscat_s(buffer, L"\n");

    std::string str;
    str.assign(buffer, buffer + wcslen(buffer));

    logs_.push_back(str);
    va_end(args);
}
