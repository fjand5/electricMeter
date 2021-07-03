#include "./src/webserver.h"
#include "./src/config.h"
#include "./src/mqtt.h"
#include <PZEM004Tv30.h>

extern PZEM004Tv30 pzem;
void renderUI(){
     // render
    renderInputText("Giá trị hiện tại","pzem-voltage","Điện áp","{}");
    renderInputText("Giá trị hiện tại","pzem-current","Dòng điện","{}");
    renderInputText("Giá trị hiện tại","pzem-power","Công suất","{}");
    renderInputText("Giá trị hiện tại","pzem-energy","Số điện","{}");
    renderInputText("Giá trị hiện tại","pzem-pf","Hệ số","{}");
    renderInputText("Giá trị hiện tại","pzem-frequency","Tần số","{}");


    renderChartView("Thống kê","pzem-chart-power","Thống kê trong 24 giờ",R"({
            "labels":[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24],
            "yMin":0,
            "yMax":3000
    })");

    renderButton("Thiết lập","pzem-resetEnergy","Đặt lại số điện","{}",[](String key, String val){
        pzem.resetEnergy();
    });




}