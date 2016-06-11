// Ionic Starter App

// angular.module is a global place for creating, registering and retrieving Angular modules
// 'starter' is the name of this angular module example (also set in a <body> attribute in index.html)
// the 2nd parameter is an array of 'requires'
// 'starter.services' is found in services.js
// 'starter.controllers' is found in controllers.js
var nottt = angular.module('starter', ['ionic', 'ngCordova'])
//['ionic', 'starter.controllers', 'starter.services'])

nottt.run(function($ionicPlatform) {
  $ionicPlatform.ready(function() {
    // Hide the accessory bar by default (remove this to show the accessory bar above the keyboard
    // for form inputs)
    if (window.cordova && window.cordova.plugins && window.cordova.plugins.Keyboard) {
      cordova.plugins.Keyboard.hideKeyboardAccessoryBar(true);
      cordova.plugins.Keyboard.disableScroll(true);

    }
    if (window.StatusBar) {
      // org.apache.cordova.statusbar required
      StatusBar.styleDefault();
    }
  });
})

nottt.config(function($stateProvider, $urlRouterProvider) {

  // Ionic uses AngularUI Router which uses the concept of states
  // Learn more here: https://github.com/angular-ui/ui-router
  // Set up the various states which the app can be in.
  // Each state's controller can be found in controllers.js
  $stateProvider

  //estado config
  .state('config', {
    url: '/config',
    templateUrl: 'templates/config.html',
    controller: 'ConfigCtrl'
  })

  // setup an abstract state for the tabs directive
    .state('tab', {
    url: '/tab',
    abstract: true,
    templateUrl: 'templates/tabs.html'
  })

  // Each tab has its own nav history stack:

  .state('tab.notes', {
      url: '/notes',
      views: {
        'tab-notes': {
          templateUrl: 'templates/tab-notes.html',
          controller: 'NotesCtrl'
        }
      }
    })
    .state('tab.note-detail', {
      url: '/notes/:noteId/:nname',
      views: {
        'tab-notes': {
          templateUrl: 'templates/note-detail.html',
          controller: 'NotesDetailCtrl as notdetc'
        }
      }
    })


  // if none of the above states are matched, use this as the fallback
  $urlRouterProvider.otherwise('/config');

});
