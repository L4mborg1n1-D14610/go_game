#include <gtest/gtest.h>
#include <MainMenu.hpp>

TEST(Button_tests, add_letter) {
  int score = 2;
  Button b(2, 2, score, 10);
  b.add_letter('a');
  EXPECT_EQ(b.get_text(), "2a");
}
TEST(Button_tests, delete_letter) {
    int score = 2;
    Button b(2, 2, score, 10);
    b.add_letter('a');
    EXPECT_EQ(b.get_text(), "2a");
    b.delete_letter();
    EXPECT_EQ(b.get_text(), "2");
}
TEST(Button_tests, empty_text) {
    Button b(2, 2, "text", 10);
    b.emptytext();
    EXPECT_EQ(b.get_text(), "");
}
TEST(Button_tests, isempty) {
    Button b(2, 2, "text", 10);
    b.emptytext();
    EXPECT_TRUE(b.isempty());
}
TEST(Button_tests, change_text) {
    Button b(2, 2, "1", 10);
    int a = 3;
    b.change_text(a);
    EXPECT_EQ(b.get_text(), "3");
}

TEST(Table_tests, return_tablesize) {
    Table t_1(1);
    Table t_2(2);
    Table t_3(3);
    EXPECT_EQ(t_1.return_tablesize(), 1);
    EXPECT_EQ(t_2.return_tablesize(), 2);
    EXPECT_EQ(t_3.return_tablesize(), 3);
}
TEST(Table_tests, get_doats_coordinate_x) {
    Table t_1(1);
    Table t_2(2);
    Table t_3(3);
    std::vector<int>  doats_coordinate_x_1;
    std::vector<int>  doats_coordinate_x_2;
    std::vector<int>  doats_coordinate_x_3;
    for (auto i = 0; i < 9; ++i) {
        doats_coordinate_x_1.push_back(round(115 + 77.625 * i));
    }
    for (auto i = 0; i < 13; ++i) {
        doats_coordinate_x_2.push_back(round(83 + 56.33 * i));
    }
    for (auto i = 0; i < 19; ++i) {
        doats_coordinate_x_3.push_back(59 + 40 * i);
    }
    EXPECT_EQ(t_1.get_doats_coordinate_x(), doats_coordinate_x_1);
    EXPECT_EQ(t_2.get_doats_coordinate_x(), doats_coordinate_x_2);
    EXPECT_EQ(t_3.get_doats_coordinate_x(), doats_coordinate_x_3);
}
TEST(Table_tests, get_doats_coordinate_y) {
    Table t_1(1);
    Table t_2(2);
    Table t_3(3);
    std::vector<int>  doats_coordinate_y_1;
    std::vector<int>  doats_coordinate_y_2;
    std::vector<int>  doats_coordinate_y_3;
    for (auto i = 0; i < 9; ++i) {
        doats_coordinate_y_1.push_back(round(114 + 77.625 * i));
    }
    for (auto i = 0; i < 13; ++i) {
        doats_coordinate_y_2.push_back(round(82 + 56.33 * i));
    }
    for (auto i = 0; i < 19; ++i) {
        doats_coordinate_y_3.push_back(60 + 40 * i);
    }
    EXPECT_EQ(t_1.get_doats_coordinate_y(), doats_coordinate_y_1);
    EXPECT_EQ(t_2.get_doats_coordinate_y(), doats_coordinate_y_2);
    EXPECT_EQ(t_3.get_doats_coordinate_y(), doats_coordinate_y_3);
}

TEST(math_fiuctions_tests, in_circle) {
    int x;
    int y;
    int r;
    int x_m;
    int y_m;
    r = 4;
    x_m = 0;
    y_m = 0;
    x = 2;
    y = 3;
    EXPECT_TRUE(_in_circle(x, y, r, x_m, y_m));
}

TEST(TableStone_tests, operators) {
    int x;
    int y;
    x = 2;
    y = 3;
    Table t(1);
    TableStone ts(x, y, t, true);
    TableStone ts_1;
    ts_1 = ts;
    EXPECT_TRUE(ts_1 == TableStone(x, y, t, true));
}
TEST(TableStone_tests, check_stone) {
    int x;
    int y;
    x = 2;
    y = 3;
    Table t(1);
    TableStone ts(x, y, t, true);
    int x_y_zero;
    x_y_zero = 0;
    TableStone ts_1(x_y_zero, x_y_zero, t, true);
    EXPECT_TRUE(ts.check_stone());
    EXPECT_FALSE(ts_1.check_stone());
}
TEST(TableStone_tests, check_color) {
    int x;
    int y;
    x = 2;
    y = 3;
    Table t(1);
    TableStone ts(x, y, t, true);
    TableStone ts_1(x, y, t, false);
    EXPECT_TRUE(ts.check_color());
    EXPECT_FALSE(ts_1.check_color());
}
TEST(TableStone_tests, stone_coords_pixels) {
    int x;
    int y;
    x = 2;
    y = 3;
    Table t(1);
    TableStone ts(x, y, t, true);
    std::pair<int, int> ts_pair = std::make_pair(x, y);
    EXPECT_EQ(ts.stone_coords_pixels(), ts_pair);
}
TEST(TableStone_tests, get_x_y) {
    int x;
    int y;
    x = 2;
    y = 3;
    Table t(1);
    TableStone ts(x, y, t, true);
    EXPECT_EQ(ts.get_x(), x);
    EXPECT_EQ(ts.get_y(), y);
}

TEST(for_MainMenu, return_stone_coordinate) {
    int t_1 = 1;
    int t_2 = 2;
    int t_3 = 3;
    std::pair<int, int> p_1 = std::make_pair(0, 1);
    std::pair<int, int> p_2 = std::make_pair(2, 3);
    std::pair<int, int> p_3 = std::make_pair(4, 5);
    EXPECT_EQ(return_stone_coordinate(p_1, t_1), std::make_pair(115, 192));
    EXPECT_EQ(return_stone_coordinate(p_2, t_2), std::make_pair(196, 251));
    EXPECT_EQ(return_stone_coordinate(p_3, t_3), std::make_pair(219, 260));
}
TEST(for_MainMenu, middlescreens) {
    int x;
    x = 9;
    int y;
    y = 12;
    EXPECT_EQ(middlescreenX(x), 4);
    EXPECT_EQ(middlescreenY(y), 6);
}
TEST(for_MainMenu, check_press) {
    std::vector<bool> vec;
    for (auto i = 0; i < 3; ++i) {
        vec.push_back(true);
    }
    for (auto i = 0; i < 3; ++i) {
        vec.push_back(false);
    }
    EXPECT_TRUE(check_press(vec, 4, 2));
    EXPECT_FALSE(check_press(vec, 4, 5));
}