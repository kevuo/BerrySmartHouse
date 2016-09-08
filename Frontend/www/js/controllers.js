angular.module('app')

.controller('surveillanceCameraCtrl', ['$scope', '$stateParams', // The following is the constructor function for this page's controller. See https://docs.angularjs.org/guide/controller
// You can include any angular dependencies as parameters for this function
// TIP: Access Route Parameters for your page via $stateParams.parameterName
function ($scope, $stateParams) {


}])
   
.controller('homeLightingCtrl', ['$scope', '$stateParams', // The following is the constructor function for this page's controller. See https://docs.angularjs.org/guide/controller
// You can include any angular dependencies as parameters for this function
// TIP: Access Route Parameters for your page via $stateParams.parameterName
function ($scope, $stateParams) {


}])
   
.controller('doorControlCtrl', ['$scope', '$stateParams', // The following is the constructor function for this page's controller. See https://docs.angularjs.org/guide/controller
// You can include any angular dependencies as parameters for this function
// TIP: Access Route Parameters for your page via $stateParams.parameterName
function ($scope, $stateParams) {


}])
.controller('MainCtrl', function($scope, AuthService, API_ENDPOINT, $http, $state){
	$scope.logout=function(){
		AuthService.logout();
		$state.go('main.login');
};	
})

.controller('pleaseSignInCtrl', function($scope, AuthService, $ionicPopup, $state){
	$scope.user= {
		name: '',
		password: ''
	};

	$scope.login= function(){
		AuthService.login($scope.user).then(function(msg){
		  $state.go('tabsController');
		}, function(errMsg){
			var alertPopup = $ionicPopup.alert({
				title: 'Login failed!',
				template: errMsg
			});
		});
	};
})

.controller('AppCtrl', function($scope, $state, $ionicPopup, AuthService, AUTH_EVENTS) {
	$scope.$on(AUTH_EVENTS.notAuthenticated, function(event) {
		AuthService.logout();
		$state.go('main.login');
		var alertPopup = $ionicPopup.alert({
			title: 'Session Lost!',
			template: 'Sorry, you have to log in again.'
		});
	});
	});
