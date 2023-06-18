//PATRON BRIDGE
//NOEMI NOELIA GONZALES PEREIRA
//CARRERA: ING. SISTEMAS
#include <iostream>
#include <vector>
using namespace std;
class Device {
public:
	virtual bool isEnabled() const = 0;
	virtual void enable() = 0;
	virtual void disable() = 0;
	virtual float getVolume() const = 0;
	virtual void setVolume(float percent) = 0;
	virtual float getChannel() const = 0;
	virtual void setChannel(float channel) = 0;
};

class RemoteControl {
protected:
	Device* device;

public:
	RemoteControl(Device* device) {
		this->device = device;
	}

	void togglePower() {
		if (device->isEnabled()) {
			device->disable();
		}
		else {
			device->enable();
		}
	}

	void volumeDown() {
		device->setVolume(device->getVolume() - 10);
	}

	void volumeUp() {
		device->setVolume(device->getVolume() + 10);
	}

	void channelDown() {
		device->setChannel(device->getChannel() - 1);
	}

	void channelUp() {
		device->setChannel(device->getChannel() + 1);
	}
	void setChannel(float channel) {
		device->setChannel(channel);
	}
};

class AdvancedRemoteControl : public RemoteControl {
public:
	AdvancedRemoteControl(Device* device) : RemoteControl(device) {}

	void mute() {
		device->setVolume(0);
	}
	void setChannel(float channel) {
		device->setChannel(channel);
	}
};


class Canal {
private:
	int numero;
	string nombre;

public:
	Canal(int numero, const string& nombre) : numero(numero), nombre(nombre) {}

	int getNumero() const {
		return numero;
	}

	string getNombre() const {
		return nombre;
	}
};

class Tv : public Device {
private:
	bool estado;
	int volumen;
	vector<Canal> canales;
	string marca;

public:
	Tv(const string& marca) : estado(false), volumen(50), marca(marca) {}

	bool isEnabled() const {
		return estado;
	}

	void enable() {
		estado = true;
	}

	void disable() {
		estado = false;
	}

	float getVolume() const {
		return volumen;
	}

	void setVolume(float percent) {
		if (percent >= 0.0 && percent <= 100.0) {
			volumen = percent;
		}
	}

	float getChannel() const {
		// Si no hay canales configurados, retorna -1
		if (canales.empty()) {
			return -1.0;
		}

		// Retorna el número del canal actual
		return canales[0].getNumero();
	}

	void setChannel(float channel) {
		// Si el canal existe, lo establece como el canal actual
		for (const auto& canal : canales) {
			if (canal.getNumero() == channel) {
				cout << "Cambiando al canal " << canal.getNumero() << ": " << canal.getNombre() << endl;
				return;
			}
		}

		// Si no se encontró el canal, muestra un mensaje de error
		cout << "El canal " << channel << " no está disponible." <<endl;
	}

	void addCanal(const Canal& canal) {
		canales.push_back(canal);
	}

	void printMarca() const {
		cout << "Marca de TV: " << marca << endl;
	}
};

class Radio : public Device {
private:
	bool estado;
	float volumen;
	float canal;

public:
	Radio() : estado(false), volumen(50.0), canal(100.0) {}

	bool isEnabled() const {
		return estado;
	}
	void enable() {
		estado = true;
	}

	void disable() {
		estado = false;
	}

	float getVolume() const {
		return volumen;
	}

	void setVolume(float percent) {
		if (percent >= 0.0 && percent <= 100.0) {
			volumen = percent;
		}
	}
	float getChannel() const {
		return canal;
	}

	void setChannel(float channel) {
		canal = channel;
	}
};
class Pelicula {
private:
	string titulo;

public:
	Pelicula(const string& titulo) : titulo(titulo) {}

	string getTitulo() const {
		return titulo;
	}
};

class Servicio {
private:
	string nombre;
	vector<Pelicula> listaPeliculas;

public:
	Servicio(const string& nombre) : nombre(nombre) {}

	string getNombre() const {
		return nombre;
	}

	void agregarPelicula(const Pelicula& pelicula) {
		listaPeliculas.push_back(pelicula);
	}

	void mostrarPeliculas() const {
		cout << "Peliculas disponibles en " << nombre << ":" << endl;
		for (const auto& pelicula : listaPeliculas) {
			cout << pelicula.getTitulo() << endl;
		}
	}
};

class TvBox {
private:
	bool estado;
	float volumen;
	string servicioActual;
	string peliculaActual;

public:
	TvBox() : estado(false), volumen(50.0) {}

	bool isEnabled() const {
		return estado;
	}

	void enable() {
		estado = true;
	}

	void disable() {
		estado = false;
	}

	float getVolume() const {
		return volumen;
	}

	void setVolume(float percent) {
		if (percent >= 0.0 && percent <= 100.0) {
			volumen = percent;
		}
	}

	string getService() const {
		return servicioActual;
	}

	void setService(const string& servicio) {
		servicioActual = servicio;
	}

	string getCurrentMovie() const {
		return peliculaActual;
	}

	void setCurrentMovie(const string& pelicula) {
		peliculaActual = pelicula;
	}
};
class TvBoxRemoteControl : public RemoteControl {
private:
	TvBox* tvBox;

public:
	TvBoxRemoteControl(TvBox* tvBox); //: RemoteControl(tvBox) {}

	void setService(const string& service) {
		tvBox->setService(service);
	}

	void setCurrentMovie(const string& movie) {
		tvBox->setCurrentMovie(movie);
	}
};
int main() {

	cout << "sistema de control remoto" << endl;
	Tv tv(" ");
	Radio radio;
	//TvBox tvBox;


	cout << "Seleccione el dispositivo a controlar:" << endl;
	cout << "1. TV" << endl;
	cout << "2. Radio" << endl;
	cout << "3. TV Box" << endl;
	int opcion;
	cin >> opcion;
	cin.ignore();

	RemoteControl* remote = nullptr;

	switch (opcion) {
	case 1:
		remote = new RemoteControl(&tv);
		break;
	case 2:
		remote = new AdvancedRemoteControl(&radio);
		break;
		//case 3:
			//remote = new RemoteControl(&tvBox);
			//break;
	default:
		cout << "Opcion invalida." << endl;
		return 0;
	}

	cout << "Controlando el dispositivo seleccionado." << endl;
	cout << "Seleccione una opcion:" << endl;
	cout << "1. Encender/Apagar" << endl;
	cout << "2. Subir volumen" << endl;
	cout << "3. Bajar volumen" << endl;
	cout << "4. Cambiar canal" << endl;

	int opcionControl;
	cin >> opcionControl;
	cin.ignore();


	switch (opcionControl) {
	case 1:
		remote->togglePower();
		break;
	case 2:
		remote->volumeUp();
		break;
	case 3:
		remote->volumeDown();
		break;
	case 4:
		float nuevoCanal;
		cout << "Introduce el numero del nuevo canal: ";
		cin >> nuevoCanal;
		cin.ignore();
		remote->setChannel(nuevoCanal);
		break;
	default:
		cout << "Opcion invalida." << endl;
		delete remote;
		return 0;
	}

	cout << "Operacion completada." << endl;
	delete remote;
	return 0;
}


