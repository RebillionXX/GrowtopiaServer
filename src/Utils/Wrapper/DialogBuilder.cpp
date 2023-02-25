#include <Utils/Wrapper/DialogBuilder.hpp>

DialogBuilder::DialogBuilder() : m_result() {}
DialogBuilder::~DialogBuilder() { m_result.clear(); }

std::string DialogBuilder::GetSize(uint8_t size) const {
    switch (size) {
        case eSizeType::SMALL:
            return "small";
        default:
            return "big";
    }
}
std::string DialogBuilder::GetDirection(uint8_t direction) const {
    switch (direction) {
    case eDirection::LEFT:
        return "left";
    case eDirection::RIGHT:
        return "right";
    case eDirection::STATIC_BLUE_FRAME:
        return "staticBlueFrame";
    }
    return "";
}

DialogBuilder* DialogBuilder::SetDefaultColor(char color) {
    m_result.append(fmt::format("\nset_default_color|`{}", color));
    return this;
}

DialogBuilder* DialogBuilder::TextScalingString(std::string scale) {
    m_result.append(fmt::format("\ntext_scaling_string|{}", scale));
    return this;
}

DialogBuilder* DialogBuilder::EmbedData(std::string name, std::string value) {
    m_result.append(fmt::format("\nembed_data|{}|{}", name, value));
    return this;
}
template<typename T, typename std::enable_if_t<std::is_integral_v<T>, bool>>
DialogBuilder* DialogBuilder::EmbedData(std::string name,  T value) {
    m_result.append(fmt::format("\nembed_data|{}|{}", name, std::to_string((int32_t)value)));
    return this;
}
template<typename T, typename std::enable_if_t<std::is_floating_point_v<T>, bool>>
DialogBuilder* DialogBuilder::EmbedData(std::string name, T value) {
    if (std::is_same_v<T, double>)
        m_result.append(fmt::format("\nembed_data|{}|{}", name, std::stod(value)));
    else if (std::is_same_v<T, long double>)
        m_result.append(fmt::format("\nembed_data|{}|{}", name, std::stold(value)));
    else
        m_result.append(fmt::format("\nembed_data|{}|{}", name, std::stof(value)));
    return this;
}

DialogBuilder* DialogBuilder::AddCustomBreak() {
    m_result.append("\nadd_custom_break|");
    return this;
}
DialogBuilder* DialogBuilder::AddSpacer(eSizeType size) {
    m_result.append(fmt::format("\nadd_spacer|{}|", this->GetSize(size)));
    return this;
}
DialogBuilder* DialogBuilder::SetCustomSpacing(int32_t x, int32_t y) {
    m_result.append(fmt::format("\nset_custom_spacing|x:{};y:{}|", x, y));
    return this;
}
DialogBuilder* DialogBuilder::AddLabel(std::string label, eDirection direction, eSizeType size) {
    m_result.append(fmt::format("\nadd_label|{}|{}|{}|0|", this->GetSize(size), label, this->GetDirection(direction)));
    return this;
}
DialogBuilder* DialogBuilder::AddLabelWithIcon(std::string label, int32_t itemId, eDirection direction, eSizeType size) {
    m_result.append(fmt::format("\nadd_label_with_icon|{}|{}|{}|{}|", this->GetSize(size), label, this->GetDirection(direction), itemId));
    return this;
}
DialogBuilder* DialogBuilder::AddCustomLabel(std::string label, std::string target, double top, double left, eSizeType size) {
    m_result.append(fmt::format("\nadd_custom_label|{}|target:{};top:{};left:{};size:{}|", label, target, top, left, this->GetSize(size)));
    return this;
}
DialogBuilder* DialogBuilder::AddTextbox(std::string label) {
    m_result.append(fmt::format("\nadd_textbox|{}|", label));
    return this;
}
DialogBuilder* DialogBuilder::AddSmallText(std::string label) {
    m_result.append(fmt::format("\nadd_smalltext|{}|", label));
    return this;
}
DialogBuilder* DialogBuilder::AddTextInput(std::string name, std::string label, std::string labelInside, int32_t maxLength) {
    m_result.append(fmt::format("\nadd_text_input|{}|{}|{}|{}|", name, label, labelInside, maxLength));
    return this;
}
DialogBuilder* DialogBuilder::AddTextInputPassword(std::string name, std::string label, std::string labelInside, int32_t maxLength) {
    m_result.append(fmt::format("\nadd_text_input_password|{}|{}|{}|{}|", name, label, labelInside, maxLength));
    return this;
}
DialogBuilder* DialogBuilder::AddTextboxInput(std::string name, std::string label, std::string textInside, int32_t maxLength, int32_t lines) {
    return this;
}
DialogBuilder* DialogBuilder::AddButton(std::string name, std::string label, std::string buttonFlag) {
    m_result.append(fmt::format("\nadd_button|{}|{}|{}|0|0|", name, label, buttonFlag));
    return this;
}

DialogBuilder* DialogBuilder::EndDialog(std::string name, std::string cancel, std::string ok) {
    m_result.append(fmt::format("\nend_dialog|{}|{}|{}|", name, cancel, ok));
    return this;
}