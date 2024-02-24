cmake_minimum_required(VERSION 3.13)

project(res VERSION 0.1 LANGUAGES CXX)

qt_add_resources(app "app_images"
    PREFIX "/"
    FILES
        icons/create_brush.png
        icons/create_object.png
        icons/create_template.png
        icons/move_xy.png
        icons/selection.png
        icons/qspinbox_button_up.png
        icons/qspinbox_button_down.png
        icons/qspinbox_button_up_on.png
        icons/qspinbox_button_down_on.png

        qss/dark.css
)
