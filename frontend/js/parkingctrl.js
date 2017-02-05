var parkMtApp = angular.module('parkMtApp',[]);


parkMtApp.controller("parkingCtrl",function($scope, $rootScope,$http){
  $scope.buildings = ["FAIR","EHS","AMG","VET","KOM","PH","JUB","ING","ALOF","ALUM","PCS","TODD",
    "KUC","JH","FH","SFA","WMB","BDA","CKNB","TMC","TLC","HOB","HMA","SAG","BAS","COE","BRAGG","LIB",
    "HONR","SCI","LRC","WPS","DSB","BH","UP","HARR","VA","HC","GH"];

  $scope.parking = ["R","MT","FV","GL","CG","LS","GH","BS","IN","IS","PS","M","EZ","RC","MG","SB","ML","RF"];

  $scope.colors = ["#0066cc","#ffda7c","#f74545"];
  //$scope.parkingView = {"svg_2":"green"};
  $scope.sliderVal = 0;
  $scope.densityData = [];


  $scope.DensityToColorMap = function(density){
    var maxResValue = $scope.colors.length;
    var maxDensity = 25;
    return Math.round(((density)*maxResValue)/maxDensity);
  }


  // User changed slider or day -- change the map
  $scope.RefreshDensityMap = function(hour,day,map){
    var scaledDensity = 0;
    if(map == "building"){
      for (bIndex in $scope.buildings){
        if(typeof $scope.densityData[$scope.buildings[bIndex]] != "undefined"){
          if(typeof $scope.densityData[$scope.buildings[bIndex]][hour] != "undefined"){
            if(typeof $scope.densityData[$scope.buildings[bIndex]][hour][day] != "undefined"){
              scaledDensity = $scope.DensityToColorMap($scope.densityData[$scope.buildings[bIndex]][hour][day]);
              $("#"+$scope.buildings[bIndex]).attr("fill",$scope.colors[scaledDensity]);
            }
          }
        }
      }
    }
    else if(map == "parking"){
      for (pIndex in $scope.parking){
        if(typeof $scope.densityData[$scope.buildings[pIndex]] != "undefined"){
          if(typeof $scope.densityData[$scope.buildings[pIndex]][hour] != "undefined"){
            if(typeof $scope.densityData[$scope.buildings[pIndex]][hour][day] != "undefined"){
              scaledDensity = $scope.DensityToColorMap($scope.densityData[$scope.buildings[pIndex]][hour][day]);
              $("#"+$scope.buildings[pIndex]).attr("fill",$scope.colors[scaledDensity]);
            }
          }
        }
      }
    }
  }

  $scope.SelectDay = function(dayVal,dayBtn,map){
    $("#selectedDay").val(dayVal);
    $("#monBtn").attr("class","btn btn-primary");
    $("#tuesBtn").attr("class","btn btn-primary");
    $("#wedBtn").attr("class","btn btn-primary");
    $("#thurBtn").attr("class","btn btn-primary");
    $("#friBtn").attr("class","btn btn-primary");
    $("#"+dayBtn).attr("class","btn btn-success");
    $scope.RefreshDensityMap($scope.sliderVal,dayVal,map);
  }

  $scope.SelectMap = function(map){
    $scope.GrabJson(map);
    if(map == "building"){
      $("#parking").hide();
      $("#building").show();
      $("#selectedMap").val(map);
      $("#parkBtn").attr("class","btn btn-primary");
      $("#buildBtn").attr("class","btn btn-success");
    }
    else{
      $("#parking").show();
      $("#building").hide();
      $("#selectedMap").val(map);
      $("#parkBtn").attr("class","btn btn-success");
      $("#buildBtn").attr("class","btn btn-primary");
    }
  }

  // Get the JSON -- Call from Document.ready in main html page
  $scope.GrabJson = function(map){
    $http({
      method: "GET",
      url: map+"\\jsonStr.json"
      }).then(function success(response){
        //console.log(response.data);
        //var myArray = JSON.parse(response.data);
        $scope.densityData = response.data;
        //alert($scope.densityData["KOM"]);
        //console.log($scope.densityData["KOM"][3][20]);
        $scope.RefreshDensityMap(0,0,map);
      },function error(response){
        alert(response.statusText);
    });
  }
});
