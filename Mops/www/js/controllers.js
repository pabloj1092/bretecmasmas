//se declara una variable global que es la base de datos
var db = null;

//var nottt = angular.module('starter', ['ionic', 'ngCordova'])

nottt.controller('ConfigCtrl', function($scope, $ionicPlatform, $ionicLoading, $location, $ionicHistory, $cordovaSQLite) {
  // With the new view caching in Ionic, Controllers are only called
  // when they are recreated or on app start, instead of every page change.
  // To listen for when this page is active (for example, to refresh data),
  // listen for the $ionicView.enter event:
  //
  //$scope.$on('$ionicView.enter', function(e) {
  //});
  $ionicHistory.nextViewOptions({
      disableAnimate: true,
      disableBack: true
  });
  $ionicPlatform.ready(function() {
      //Template de ionic q permite mostrar una pequeña ventana de loading mientras se ejecutan acciones en segundo plano
      $ionicLoading.show({ template: 'Loading...' });
      //Reconoce si está en un celular
      if(window.cordova) {
          // alert("Estamos en un celular")
          //Abre la comunicación con la base de datos
          //utilizando el plugin de Cordova directamente
          db = window.sqlitePlugin.openDatabase({name: 'new.db', location: 'default', androidDatabaseImplementation: 2});

          //Ejecuta un Batch de SQL.. un batch es una accion de tramas que permite se hagan las acciones, pero todas deben de realizarse
          //antes de realizar cualquier otra. Pone un lock y hace rollup en caso de que alguna falle.
          //La sintaxis es: sqlBatch([arrreglo de instrucciones de SQL],funcion que se llama si todo sale bien, funcion que se llama si algo dio error)

          db.sqlBatch([
            //Se borra la tabla si existe (esto se hace porq todas las veces que el app inicie va a agregar
            //dos categorias de compras y univeridad. por lo que si borramos la tabla y la volvemos a crear,
            //siempre se veran solo dos... es un truco pero claramente no se hace, es solo para el ejemplo :P )
            //si quieren mejorarlo pueden hacer q las categorias se puedan crear dinamicamente igual que las listas
            //y los items.
            "DROP TABLE IF EXISTS tblNotes",
            //Crea las siguientes tablas con las siguientes características si no existen
            "CREATE TABLE IF NOT EXISTS tblNotes (id integer primary key, note_name text)",
            "CREATE TABLE IF NOT EXISTS tblTexts (id integer primary key, note_id integer, note_text text)",
            //inserta dos categorias "hardcoded" solo para pruebas
            ["INSERT INTO tblNotes (note_name) VALUES (?)", ["Brete"]],
            ["INSERT INTO tblNotes (note_name) VALUES (?)", ["Universidad"]]
          ], function() {
              //funcion que se llama si todo sale bien
              //Redirige el app al url de /categories
              $location.path("/tab/notes");
              //esconde la ventana de loading que se mostró anteriormente
              $ionicLoading.hide();

              //Prestar atención que estos llamados son a $location para cambiar de ventana y a .hide() para
              //esconder el loading..., son realizados luego de que el Batch termine, ya que es en la función
              //que llama luedo de que todo saliera bien

          }, function(error) {
            console.log('Populate table error: ' + error.message);
          });
      } else {
          // si no esta en un telefono, sino que esta en un browser, realiza lo siguiente:
          // No escribí nada porque no estamos desarrollando para navegadores. es útil para hacer debug
          // pero no hace falta si van a estar trabajando en vivo en el telefono con el comando:

          // $ ionic run android -c -l

          // $location.path("/categories");
          // $ionicLoading.hide();
          alert("Estamos en un browser")
      }
  });
})


nottt.controller("NotesCtrl", function($scope, $ionicPlatform, $cordovaSQLite, $ionicPopup, $stateParams) {

  db = window.sqlitePlugin.openDatabase({name: 'new.db', location: 'default', androidDatabaseImplementation: 2});

  //Una variable de scope que se puede acceder desde el html utilizando la sintaxis {{ --- }} de angularjs.
  //es un arreglo
  $scope.notes = [];

  //se espera que la plataforma de ionic este lista para realizar operaciones (es una buena práctica)
  $ionicPlatform.ready(function() {
    //alistamos el query de SQL que vamos a realizar.
    //el query tiene esta sintaxis:
    //  seleccione id y catergory_name de la tabla tblCategories
    var query = "SELECT id, note_name FROM tblNotes";

    //abre la conexion con la base de datos
    //db = window.sqlitePlugin.openDatabase({name: 'new.db', location: 'default', androidDatabaseImplementation: 2});

    //ejecuta el query. la sintaxis es similar:
    //executeSql(string del query a realizar, paramentros, funcion que se llama si todo sale bien, funcion q se llama si algo sale mal)

    db.executeSql(query,  [], function (resultSet) {
      //esta funcion se llama si sale bien.
      //resultSet es la tabla resultante del query a la base de datos
      //Si la longitud es mayor a 0, es decir, si al menos hay un elemento
      if(resultSet.rows.length > 0) {
          //recorra todos los elementos
           for(var i = 0; i < resultSet.rows.length; i++) {
              //agregue dicho elemento en forma de diccionario al arreglo $scope.categories para que pueda
              //ser accedido desde la interfaz gráfica. (observe el funcionamiento del patron de diseño MVC)
               $scope.notes.push({id: resultSet.rows.item(i).id, note_name: resultSet.rows.item(i).note_name});
           }
       }

       //se cierra la conexión con la base de datos.
      //db.close();

     }, function(error) {
        //en caso de algun error, imprime en cosola lo siguente.
         console.log('Populate table error: ' + error.message);
      });

  });

  //es la funcion que se llama desde el view (HTML) para insertar una nueva lista de que haceres
  $scope.insert = function() {
      //se utiliza ionicPopup para template de ventana de introducir datos.
      //el .then() se llama en estos templates luego de que el usuario los acepta
      $ionicPopup.prompt({
          title: 'Enter note title',
          inputType: 'text'
      })
      .then(function(result) {
          // si el usuario introdujo algo difernte de nada lo agrega a la tabla de listas
          if(result != "") {
              //preparamos el query para insertar la lista nueva
              var query = "INSERT INTO tblNotes ( note_id, note_name ) VALUES (?,?)";
              //vean que otra opción es utilizar el plugin de ngCordova para SQLite. La sintaxis es similar,
              //pero en lugar de callbacks como las otras que llaman funciones, utilizan el formato
              //.then() que ya vieron que ionic también utiliza. El .then() funciona similar, y llama dos funciones
              //una en caso de success, y otra en caso de error

              //utilizando el plugin de ngCordova, para que se hable con el original de cordova. Se hace para mantener,
              //la estructura que se acostumbra en AngularJS
              $cordovaSQLite.execute(db, query, [$stateParams.noteId, result]).then(function(res) {
                  $scope.notes.push({id: res.insertId, note_id: $stateParams.noteId, note_name: result});
              }, function (err) {
                  console.error(err);
              });
          } else {
              console.log("Action not completed");
          }
      });
  }

});





nottt.controller('NotesDetailCtrl', function($scope, $ionicPlatform, $cordovaSQLite, $ionicPopup, $stateParams) {

  $scope.texts = [];

  //se espera que la plataforma de ionic este lista para realizar operaciones (es una buena práctica)
  $ionicPlatform.ready(function() {
    var query = "SELECT id, note_id, note_text FROM tblTexts where note_id = ?";
    db.executeSql(query, [$stateParams.noteId], function (resultSet){

      //esta funcion se llama si sale bien.
      //resultSet es la tabla resultante del query a la base de datos
      //Si la longitud es mayor a 0, es decir, si al menos hay un elemento
      if(resultSet.rows.length > 0) {
          //recorra todos los elementos
           for(var i = 0; i < resultSet.rows.length; i++) {
               $scope.notes.push({id: resultSet.rows.item(i).id, note_id: resultSet.rows.item(i).note_id, note_text: resultSet.rows.item(i).note_text});
           }
       }

       //se cierra la conexión con la base de datos.
      //db.close();

     }, function(error) {
        //en caso de algun error, imprime en cosola lo siguente.
         console.log('Populate table error: ' + error.message);
      });

  });


});
