// imtest.cpp: 定义控制台应用程序的入口点。
//
//编码：
//0—未知身份
//1—好人
//2—狼人
//3—平民
//4—预言家
//5—守卫
//6—女巫
//7—白痴
//8—白狼王
//9—保留
//
//每一次对程序发一个12位字符串作为参数，参数不符合要求会无法运行，12位数对应12位玩家
//示例：
//000042000100表示5号预言家，6号狼人，10号好人，其余为未知身份

#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<string>


std::string help = "编码：\
0—未知身份\
1—好人\
2—狼人\
3—平民\
4—预言家\
5—守卫\
6—女巫\
7—白痴\
8—白狼王\
9—保留\
\
每一次对程序发一个12位字符串作为参数，参数不符合要求会无法运行，12位数对应12位玩家\
示例：\
000042000100表示5号预言家，6号狼人，10号好人，其余为未知身份";




cv::Rect pos[13];
cv::Mat im_dst;
cv::Mat image_template;

void setPlayerCard(int player, std::string role) {
	//编码：
	//0—未知身份
	//1—好人
	//2—狼人
	//3—平民
	//4—预言家
	//5—守卫
	//6—女巫
	//7—白痴
	//8—白狼王
	//9—保留


	if (role != "0") {

		cv::Mat im_role = cv::imread(role + ".jpg");
		cv::Mat image_matched;



		//模板匹配  
		cv::matchTemplate(im_dst, image_template, image_matched, cv::TM_CCOEFF_NORMED);
		double minVal, maxVal;
		cv::Point minLoc, maxLoc;
		//寻找最佳匹配位置  
		cv::minMaxLoc(image_matched(pos[player]), &minVal, &maxVal, &minLoc, &maxLoc);
		//cv::imshow("roi", image_matched(pos[player]));
		cv::Rect roi_rect = cv::Rect(pos[player].x + maxLoc.x, pos[player].y + maxLoc.y, im_role.cols, im_role.rows);
		im_role.copyTo(im_dst(roi_rect));

	}


}

int main()
{
	image_template = cv::imread("0.jpg");
	//加载源图像和模板图像  
	cv::Mat image_source = cv::imread("in.jpg");

	image_source.copyTo(im_dst);
	int s_rows = im_dst.rows;
	int s_cols = im_dst.cols;
	pos[1] = cv::Rect(0, 0 * s_rows / 2160, s_cols / 2, 338 * s_rows / 2160);
	pos[2] = cv::Rect(0, 339 * s_rows / 2160, s_cols / 2, (500 - 338) * s_rows / 2160);
	pos[3] = cv::Rect(0, 501 * s_rows / 2160, s_cols / 2, (666 - 500) * s_rows / 2160);
	pos[4] = cv::Rect(0, 667 * s_rows / 2160, s_cols / 2, (832 - 666) * s_rows / 2160);
	pos[5] = cv::Rect(0, 833 * s_rows / 2160, s_cols / 2, (994 - 832) * s_rows / 2160);
	pos[6] = cv::Rect(0, 995 * s_rows / 2160, s_cols / 2, (1167 - 994) * s_rows / 2160);

	pos[7] = cv::Rect(s_cols / 2, 0 * s_rows / 2160, s_cols / 2 - image_template.cols - 1, 338 * s_rows / 2160);
	pos[8] = cv::Rect(s_cols / 2, 339 * s_rows / 2160, s_cols / 2 - image_template.cols - 1, (500 - 338)  * s_rows / 2160);
	pos[9] = cv::Rect(s_cols / 2, 501 * s_rows / 2160, s_cols / 2 - image_template.cols - 1, (666 - 500) * s_rows / 2160);
	pos[10] = cv::Rect(s_cols / 2, 667 * s_rows / 2160, s_cols / 2 - image_template.cols - 1, (832 - 666) * s_rows / 2160);
	pos[11] = cv::Rect(s_cols / 2, 833 * s_rows / 2160, s_cols / 2 - image_template.cols - 1, (994 - 832) * s_rows / 2160);
	pos[12] = cv::Rect(s_cols / 2, 995 * s_rows / 2160, s_cols / 2 - image_template.cols - 1, (1167 - 994) * s_rows / 2160);

	std::cout << "请输入身份代号：\n" << help << std::endl;
	std::string role_table;
	std::cin >> role_table;
	if (role_table.length() != 12) {
		std::cout << "输入错误，不是12位\n";
		cv::waitKey(0);
		return 0;
	}
	for (int i = 1; i <= 12; i++) {
		setPlayerCard(i, role_table.substr(i - 1, 1));
	}
	//setPlayerCard(3, "2");
	cv::imwrite("out.png", im_dst);
	cv::waitKey(0);

	return 0;
}

