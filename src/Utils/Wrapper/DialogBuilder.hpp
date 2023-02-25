#pragma once
#include <string>
#include <fmt/core.h>

enum eSizeType : uint8_t {
    SMALL,
    BIG
};
enum eDirection : uint8_t {
    NONE,
    LEFT,
    RIGHT,
    STATIC_BLUE_FRAME
};

class DialogBuilder {
public:
    DialogBuilder();
    ~DialogBuilder();
    
    DialogBuilder* SetDefaultColor(char color);
    DialogBuilder* TextScalingString(std::string scale);

    DialogBuilder* EmbedData(std::string name, std::string value);
    template<typename T, typename std::enable_if_t<std::is_integral_v<T>, bool> = true>
    DialogBuilder* EmbedData(std::string name, T value);
    template<typename T, typename std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
    DialogBuilder* EmbedData(std::string name, T value);

    DialogBuilder* AddCustomBreak();
    DialogBuilder* AddSpacer(eSizeType size = SMALL);
    DialogBuilder* SetCustomSpacing(int32_t x, int32_t y);
    DialogBuilder* AddLabel(std::string label, eDirection direction =  LEFT, eSizeType size = SMALL);
    DialogBuilder* AddLabelWithIcon(std::string label, int32_t itemId, eDirection direction =  LEFT, eSizeType size = SMALL);
    DialogBuilder* AddCustomLabel(std::string label, std::string target, double top, double left, eSizeType size = SMALL);
    DialogBuilder* AddTextbox(std::string label);
    DialogBuilder* AddSmallText(std::string label);
    DialogBuilder* AddTextInput(std::string name, std::string label, std::string labelInside, int32_t maxLength);
    DialogBuilder* AddTextInputPassword(std::string name, std::string label, std::string labelInside, int32_t maxLength);
    DialogBuilder* AddTextboxInput(std::string name, std::string label, std::string textInside, int32_t maxLength, int32_t lines);
    DialogBuilder* AddButton(std::string name, std::string label, std::string buttonFlag = "noflags");

    DialogBuilder* EndDialog(std::string name, std::string cancel, std::string ok);

    /*DialogBuilder add_button_with_icon(std::string name, std::string label, int32_t item_id, eDirection direction =  LEFT) {
        result.append(fmt::format("\nadd_button_with_icon|{}|{}|{}|{}|", name, label, this->GetDirection(direction), item_id));
        return *this;
    }
    DialogBuilder add_button_with_icon(std::string name, std::string label, int32_t item_id, std::string description, eDirection direction =  LEFT) {
        result.append(fmt::format("\nadd_button_with_icon|{}|{}|{}|{}|{}|", name, label, this->GetDirection(direction), item_id, description));
        return *this;
    }
    DialogBuilder add_custom_button(std::string name, std::string image, int32_t image_x, int32_t image_y, const double& width) {
        result.append(fmt::format("\nadd_custom_button|{}|image:{};image_size:{},{};width:{};|", name, image, image_x, image_y, width));
        return *this;
    }
    DialogBuilder add_friend_image_label_button(std::string name, std::string label, std::string texture_path, const double& size, const CL_Vec2i& texture) {
        result.append(fmt::format("\nadd_friend_image_label_button|{}|{}|{}|{}|{}|{}|32|false|false|", name, label, texture_path, size, texture.m_x, texture.m_y));
        return *this;
    }
    DialogBuilder add_label_with_icon(std::string label, int32_t itemId, eDirection direction =  LEFT, eSizeType size = SMALL) {
        result.append(fmt::format("\nadd_label_with_icon|{}|{}|{}|{}|", this->GetSize(size), label, this->GetDirection(direction), itemId));
        return *this;
    }
    DialogBuilder add_label_with_icon_button(std::string name, std::string label, int32_t itemId, eDirection direction =  LEFT, eSizeType size = SMALL);
    DialogBuilder add_dual_layer_icon_label(std::string label, const std::pair<int, int>& icon, const double& size, eDirection direction =  LEFT, eSizeType size = SMALL) {
        result.append(fmt::format("\nadd_dual_layer_icon_label|{}|{}|{}|{}|{}|{}|0|", this->GetSize(size), label, this->GetDirection(direction), icon.second, icon.first, size));
        return *this;
    }
    DialogBuilder add_player_info(std::string name, int32_t level, int32_t exp, int32_t math_exp) {
        result.append(fmt::format("\nadd_player_info|{}|{}|{}|{}", name, level, exp, math_exp));
        return *this;
    }
    DialogBuilder add_item_picker(std::string name, std::string label, std::string floating_text) {
        result.append(fmt::format("\nadd_item_picker|{}|{}|{}|", name, label, floating_text));
        return *this;
    }
    DialogBuilder add_player_picker(std::string name, std::string label) {
        result.append(fmt::format("\nadd_player_picker|{}|{}", name, label));
        return *this;
    }
    DialogBuilder add_checkbox(std::string name, std::string label, const bool& active) {
        result.append(fmt::format("\nadd_checkbox|{}|{}|{}", name, label, active ? "1" : "0"));
        return *this;
    }
    DialogBuilder add_checkicon(std::string name, std::string label, int32_t id, std::string frame_message, const bool& enabled) {
        result.append(fmt::format("\nadd_checkicon|{}|{}|staticframe|{}|{}|{}", name, label, id, frame_message, enabled ? "1" : "0"));
        return *this;
    }
    DialogBuilder add_quick_exit() {
        result.append("\nadd_quick_exit|");
        return *this;
    }*/

public:
    std::string Get() const { return m_result; }
    operator std::string() { return m_result; }

private:
    std::string GetSize(uint8_t size) const;
    std::string GetDirection(uint8_t direction) const;

private:
    std::string m_result;
};