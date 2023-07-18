# AI-nalyst

### 개발환경
* Linux
* Python
    * Pytorch
    * sklearn
    * Pandas
    * Numpy
    * django
* PostgreSQL

### 개요
- 증권사 리포트를 작성하는 애널리스트와 기업간의 이해관계에 의해 솔직하지 못하게 작성되는 투자의견을 AI 모델로 새롭게 투자의견을 제시.

### 목표
- 애널리스트가 작성한 리포트의 맥락을 분석해서​ 새로운 투자 의견을 도출해내는 인공지능 시스템 구현​.
-  경제, 금융 관련 리포트의 맥락, 의도를 분석하는 딥러닝 모델 개발 (Bert 계열 모델 활용)​.
-  다양한 전처리 기법으로 테스트하며 최적의 성능을 도출​.
-  부족한 리포트 데이터로 인한 성능 저하를 보완하기 위한 기법 사용.
    -  data augmentation
    -  K-Fold Validation
    -  Ensemble
 
### 내용
-  System Design - Flow chart
<img width="500" alt="image" src="https://github.com/by-hwa/AI-nalyst/assets/102535447/1857bb17-de57-48fa-824e-cd986ed3dbbb">

-  System Design - Function block chart
<img width="500" alt="image" src="https://github.com/by-hwa/AI-nalyst/assets/102535447/73b706ae-3ef0-48c6-8650-5d29293ada48">

-----------------
### 1. Data Scapping
<img width="1000" height="300" alt="image" src="https://github.com/by-hwa/AI-nalyst/assets/102535447/3e970d60-893e-456f-b439-504ae65b0d33">

-    python library Selenium & Beautifulsoup 을 이용하여 리포트 스크래핑.
-  Train : 한경 컨센서스에서 스크래핑한 리포트.
-  Inference : 네이버 금융에서 스크래핑한 리포트.

### 2. Data Preprocessing
<img width="700" alt="image" src="https://github.com/by-hwa/AI-nalyst/assets/102535447/bf86dc74-7296-4be9-adb4-66e1abb34d68">
<img width="500" alt="image" src="https://github.com/by-hwa/AI-nalyst/assets/102535447/65504b1f-4c81-45dd-b12e-d2e44d388c3f">

- PDF to Text.
- 본문의 내용만 추출.
- 데이터 라벨링.

### 3. Data Argumentation
<img width="1073" alt="image" src="https://github.com/by-hwa/AI-nalyst/assets/102535447/6a8e13c8-841a-4a79-8fe8-2c71b236f180">
<img width="1033" alt="image" src="https://github.com/by-hwa/AI-nalyst/assets/102535447/7d55a832-dc7e-40a5-9364-c45af0e3701f">

- Kakaobarin/pororo, Googletranslation 을 이용하여 여러 언어로 backtranslation.
    - kakaobrain kor - en - kor
    - googletranslation kor - en - kor
    - googletranslation kor - zh-cn - kor
- Origin data + Argumentation Data *3, 기존 데이터 보다 4배 많은 데이터 확보.

### 4. Train model
- kb-albert를 제외한 kobert, Roberta 모델을 범용 corpus로 학습된 사전학습언어모델을 금융데이터로 domain adaptive fine-tuning 후.
- kb-alber, kobert, Roberta 모델 학습.

### 5. Inference model
<img width="1028" alt="image" src="https://github.com/by-hwa/AI-nalyst/assets/102535447/a659d688-9bf1-4b99-a528-90880d744a6e">

- kb-albert, kobert, Roberta 모델을 Ensemble(soft voting) 하여 Inference.
    - Model Accuracy 97%
- Naver 금융에서 스크래핑한 데이터로 Inference & display web.
