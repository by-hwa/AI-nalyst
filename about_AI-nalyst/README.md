# AI-nalyst

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
<img width="988" alt="image" src="https://github.com/by-hwa/AI-nalyst/assets/102535447/cb0eb738-4409-43c6-ba13-601f43517030">

-  System Design - Function block chart
<img width="676" alt="image" src="https://github.com/by-hwa/AI-nalyst/assets/102535447/ac2faec9-9c2e-442b-a339-1bfdc44d194a">

-----------------
1. Data Scapping
-    python library Selenium & Beautifulsoup 을 이용하여 리포트 스크래핑.
-  Train : 한경 컨센서스에서 스크래핑한 리포트.
-  Inference : 네이버 금융에서 스크래핑한 리포트.

2. Data Preprocessing
- PDF to Text.
- 본문의 내용만 추출.
3. Data Argumentation
- Papago, Googletranslation 을 이용하여 여러 언어로 backtranslation
4. Train model
- kb-albert를 제외한 kobert, Roberta 모델을 범용 corpus로 학습된 사전학습언어모델을 금융데이터로 fine-tuning.
- kb-alber, kobert, Roberta 모델 학습.
5. Inference model
- kb-albert, kobert, Roberta 모델을 Ensemble 하여 Inference.
- Naver 금융에서 스크래핑한 데이터로 Inference & display web.
   

