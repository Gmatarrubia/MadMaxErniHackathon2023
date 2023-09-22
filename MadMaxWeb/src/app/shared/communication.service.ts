import { Injectable } from '@angular/core';
import { HttpClient, HttpParams } from '@angular/common/http';
import { map, tap, take, exhaustMap } from 'rxjs/operators';

@Injectable()
export class CommunicationService {
    constructor(private http: HttpClient) {
    }

    getPrueba() {
		// this.http.get<any[]>('http://10.141.93.250:8012')
    this.http.get<any>('https://api.npms.io/v2/search?q=scope:angular')
    .subscribe(data => {
        console.log(data);
    }) 
	}
}