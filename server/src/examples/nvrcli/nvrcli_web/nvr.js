angular.module('nvrcli', [])
   .controller('nvrcliController', function($scope) {
        // change the IP address to point to your system
       $scope.baseurl = "http://192.168.1.103:9292";
       $scope.w = "400px";
});
