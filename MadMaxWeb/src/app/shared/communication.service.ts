import { Injectable } from '@angular/core';
import { HttpClient, HttpParams } from '@angular/common/http';
import { AngularFireDatabase } from '@angular/fire/compat/database';
import { Observable } from 'rxjs';

import { Automatic } from '../control/automatic/automatic.model';
import { Status } from '../status/status.model';

@Injectable()
export class CommunicationService {
    constructor(private http: HttpClient, 
      private db: AngularFireDatabase) {
    }

    getPrueba() {
      this.http.get<any[]>('http://10.141.93.250:8012')
      // this.http.get<any>('https://api.npms.io/v2/search?q=scope:angular')
      .subscribe(data => {
          console.log(data);
      }) 
	  }

    setAutomatic(data: Automatic) {
      this.http
			.put('https://mad-max-erni-default-rtdb.firebaseio.com/automatic.json', 
				data)
			.subscribe(response => {
				console.log(response);
			});
    }

    setStatus(data: Status) {
      this.http
			.put('https://mad-max-erni-default-rtdb.firebaseio.com/status.json', 
				data)
			.subscribe(response => {
				console.log(response);
			});
    }

    getData(path: string): Observable<any> {
      return this.db.object(path).valueChanges();
    }

}