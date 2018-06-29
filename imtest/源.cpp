// imtest.cpp: �������̨Ӧ�ó������ڵ㡣
//
//���룺
//0��δ֪���
//1������
//2������
//3��ƽ��
//4��Ԥ�Լ�
//5������
//6��Ů��
//7���׳�
//8��������
//9������
//
//ÿһ�ζԳ���һ��12λ�ַ�����Ϊ����������������Ҫ����޷����У�12λ����Ӧ12λ���
//ʾ����
//000042000100��ʾ5��Ԥ�Լң�6�����ˣ�10�ź��ˣ�����Ϊδ֪���

#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<string>


std::string help = "���룺\
0��δ֪���\
1������\
2������\
3��ƽ��\
4��Ԥ�Լ�\
5������\
6��Ů��\
7���׳�\
8��������\
9������\
\
ÿһ�ζԳ���һ��12λ�ַ�����Ϊ����������������Ҫ����޷����У�12λ����Ӧ12λ���\
ʾ����\
000042000100��ʾ5��Ԥ�Լң�6�����ˣ�10�ź��ˣ�����Ϊδ֪���";




cv::Rect pos[13];
cv::Mat im_dst;
cv::Mat image_template;

void setPlayerCard(int player, std::string role) {
	//���룺
	//0��δ֪���
	//1������
	//2������
	//3��ƽ��
	//4��Ԥ�Լ�
	//5������
	//6��Ů��
	//7���׳�
	//8��������
	//9������


	if (role != "0") {

		cv::Mat im_role = cv::imread(role + ".jpg");
		cv::Mat image_matched;



		//ģ��ƥ��  
		cv::matchTemplate(im_dst, image_template, image_matched, cv::TM_CCOEFF_NORMED);
		double minVal, maxVal;
		cv::Point minLoc, maxLoc;
		//Ѱ�����ƥ��λ��  
		cv::minMaxLoc(image_matched(pos[player]), &minVal, &maxVal, &minLoc, &maxLoc);
		//cv::imshow("roi", image_matched(pos[player]));
		cv::Rect roi_rect = cv::Rect(pos[player].x + maxLoc.x, pos[player].y + maxLoc.y, im_role.cols, im_role.rows);
		im_role.copyTo(im_dst(roi_rect));

	}


}

int main()
{
	image_template = cv::imread("0.jpg");
	//����Դͼ���ģ��ͼ��  
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

	std::cout << "��������ݴ��ţ�\n" << help << std::endl;
	std::string role_table;
	std::cin >> role_table;
	if (role_table.length() != 12) {
		std::cout << "������󣬲���12λ\n";
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

