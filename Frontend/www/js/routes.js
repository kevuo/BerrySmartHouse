angular.module('app')

.config(function($stateProvider, $urlRouterProvider) {

  // Ionic uses AngularUI Router which uses the concept of states
  // Learn more here: https://github.com/angular-ui/ui-router
  // Set up the various states which the app can be in.
  // Each state's controller can be found in controllers.js
  $stateProvider
    .state('main', {
    url: '/main',
    abstract: true,
    templateUrl: 'templates/main.html'
  })
      .state('tabsController.surveillanceCamera', {
    url: '/camera',
    views: {
      'tab1': {
        templateUrl: 'templates/surveillanceCamera.html',
        controller: 'surveillanceCameraCtrl'
      }
    }
  })

  .state('tabsController.homeLighting', {
    url: '/lights',
    views: {
      'tab2': {
        templateUrl: 'templates/homeLighting.html',
        controller: 'homeLightingCtrl'
      }
    }
  })

  .state('tabsController.doorControl', {
    url: '/doors',
    views: {
      'tab3': {
        templateUrl: 'templates/doorControl.html',
        controller: 'doorControlCtrl'
      }
    }
  })

  .state('tabsController', {
    url: '/currentstate',
    templateUrl: 'templates/tabsController.html',
    abstract:true
  })

  .state('main.login', {
    url: '/login',
    templateUrl: 'templates/pleaseSignIn.html',
    controller: 'pleaseSignInCtrl'
  });

$urlRouterProvider.otherwise('/main/login');

  

});