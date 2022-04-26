#include "preprocess.h"
#include "correct_angle.h""
#include "detectlip.h"
#include "histo.h"
#include <opencv2/imgproc/types_c.h>
#include <cstdlib>
RNG rng(12345);
string name = "w���ؼ�����";

int main()
{
	CascadeClassifier face_cascade, eyes_cascade;
	load_cascade(face_cascade, "haarcascade_frontalface_alt2.xml");
	load_cascade(eyes_cascade, "haarcascade_eye.xml");

	Mat image = imread(format("%s.jpg", name), IMREAD_COLOR);
	CV_Assert(image.data);
	Mat gray = preprocessing(image);

	vector<Rect> faces, eyes;
	vector<Point2d> eyes_center;
	vector<Rect> sub_obj;

	face_cascade.detectMultiScale(gray, faces, 1.1, 2, 0, Size(100, 100));

	if (faces.size() > 0)
	{
		float i = 1.15;
		while (true) {

			eyes_cascade.detectMultiScale(gray(faces[0]), eyes, i, 7, 0, Size(25, 20));

			if (eyes.size() == 2) {
				eyes_center.push_back(calc_center(eyes[0] + faces[0].tl()));
				eyes_center.push_back(calc_center(eyes[1] + faces[0].tl()));

				Point2d face_center = calc_center(faces[0]); // �� �߽� ��ǥ ���
				Mat rot_mat = calc_rotMap(face_center, eyes_center); // �� �߽���ǥ�� �� �߽���ǥ�� �󱼱����� ȸ����� ��ȯ
				Mat correct_img = correct_image(image, rot_mat, eyes_center); // ȸ����ķ� ȸ����ȯ�� �����Ͽ� ���⸦ �����ϰ�, �� ��ǥ�� ȸ����ȯ�� �����Ͽ� �ٽ� ���
				
				detect_hair(face_center, faces[0], sub_obj);
				sub_obj.push_back(detect_lip(face_center, faces[0]));
				
				Mat dstimage = Mat::zeros(correct_img(sub_obj[0]).rows, correct_img(sub_obj[0]).cols, CV_8UC3);
				Mat cannyimage;
				Canny(correct_img(sub_obj[0]), cannyimage, 10, 100);
				
				vector<vector<Point>> contours;
				vector<Vec4i> hierarchy;
				findContours(cannyimage, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
				
				double count = 0;
				for (int i = 0; i < contours.size(); i++)
				{
					count += 1;
					Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
					drawContours(dstimage, contours, i, color, 2, 8, hierarchy, 0, Point());

				}

				Mat masks[4], hists[4];
				make_masks(sub_obj, correct_img.size(), masks);
				calc_histos(correct_img, sub_obj, hists, masks);
				
				double criteria2 = compareHist(hists[2], hists[3], CV_COMP_CORREL);
				
				double tmp = (count < 200) ? 0.1 : 0.7;
				int value = (criteria2 > tmp) ? 0 : 1;
				string text = (value) ? "MAN" : "WOMAN";
				text = format("%s.jpg: ", name) + text;

				int font = FONT_HERSHEY_TRIPLEX;
				putText(image, text, Point(12, 31), font, 0.7, Scalar(0, 0, 0), 2);
				putText(image, text, Point(10, 30), font, 0.7, Scalar(0, 255, 0), 1);

				cout << text << format(" - ���絵 [����: %4.2f, �Լ�: %4.2f]\n", count, criteria2);
				imshow("correct_img", correct_img);
			}
			i += 0.05;
			if (i > 10) break;
		}
	}
	waitKey();
	return 0;
}
