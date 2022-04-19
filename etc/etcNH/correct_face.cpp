#include "preprocess.h"
#include "correct_angle.h""
#include "detectlip.h"
#include "histo.h"
#include <opencv2/imgproc/types_c.h>

int main()
{
	CascadeClassifier face_cascade, eyes_cascade;
	load_cascade(face_cascade, "haarcascade_frontalface_alt2.xml");
	load_cascade(eyes_cascade, "haarcascade_eye.xml");

	Mat image = imread("photo2.jpg", IMREAD_COLOR);
	CV_Assert(image.data);
	Mat gray = preprocessing(image);

	vector<Rect> faces, eyes;
	vector<Point2d> eyes_center;
	vector<Rect> sub_obj;

	face_cascade.detectMultiScale(gray, faces, 1.1, 2, 0, Size(100, 100));

	if (faces.size() > 0)
	{
		eyes_cascade.detectMultiScale(gray(faces[0]), eyes, 1.15, 7, 0, Size(25, 20));

		if (eyes.size() == 2) {
			eyes_center.push_back(calc_center(eyes[0] + faces[0].tl()));
			eyes_center.push_back(calc_center(eyes[1] + faces[0].tl()));

			Point2f face_center = calc_center(faces[0]); // �� �߽� ��ǥ ���
			Mat rot_mat = calc_rotMap(face_center, eyes_center); // �� �߽���ǥ�� �� �߽���ǥ�� �󱼱����� ȸ����� ��ȯ
			Mat correct_img = correct_image(image, rot_mat, eyes_center); // ȸ����ķ� ȸ����ȯ�� �����Ͽ� ���⸦ �����ϰ�, �� ��ǥ�� ȸ����ȯ�� �����Ͽ� �ٽ� ���
			// circle(correct_img, eyes_center[0], 5, Scalar(0, 255, 0), 2); // ������ �� ��ǥ�� ������ �� ���� ǥ��
			// circle(correct_img, eyes_center[1], 5, Scalar(0, 255, 0), 2);

			detect_hair(face_center, faces[0], sub_obj);
			sub_obj.push_back(detect_lip(face_center, faces[0]));
			sub_obj.push_back(detect_beard(face_center, faces[0]));
			sub_obj.push_back(detect_cheek(face_center, faces[0]));
			rectangle(correct_img, sub_obj[1], Scalar(0, 255, 0), 2);
			rectangle(correct_img, sub_obj[2], Scalar(0, 255, 0), 2);
			rectangle(correct_img, sub_obj[3], Scalar(0, 255, 0), 2);

			Mat masks[4], hists[4];
			make_masks(sub_obj, correct_img.size(), masks); // ����ũ ����
			calc_histos(correct_img, sub_obj, hists, masks); // ������׷� ����
			
			// ������׷� �� - ���絵 �� ���
			double criteria2 = compareHist(hists[1], hists[3], CV_COMP_CORREL);
			cout << format("���絵 %4.2f\n", criteria2);
			imshow("correct_img", correct_img);
			waitKey();
		}
	}
	return 0;
}
